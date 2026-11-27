

constexpr int N = 111111;
constexpr long long Mod = 998244353;

namespace Segment_Tree {
    /*
    require:
        constant: Mod N
    */

	long long tree[N << 2];
	long long add[N << 2];
	long long mult[N << 2];
	
	long long lSon (long long now) {return now * 2;}
	long long rSon (long long now) {return now * 2 + 1;}
 
	void build (long long l, long long r, long long now, long long nums[N]);
 
	void add_giveMark (long long l, long long r, long long now, long long num);
	void mult_giveMark (long long l, long long r, long long now, long long num);
 
	void pushUp (long long now);
	void pushDown (long long l, long long r, long long now);
 
	void add_update (long long allL, long long allR, long long nowL, long long nowR, long long now, long long num);
	void mult_update (long long allL, long long allR, long long nowL, long long nowR, long long now, long long num);
	long long query (long long allL, long long allR, long long nowL, long long nowR, long long now);
	
	void build (long long l, long long r, long long now, long long nums[N]) {
		add[now] = 0;
        mult[now] = 1;
		if (l == r) {
			tree[now] = nums[l];
			return;
		}
 
		long long m = (l + r) / 2;
		build (l, m, lSon (now), nums);
		build (m + 1, r, rSon (now), nums);
		pushUp (now);
	}
	
	void add_giveMark (long long l, long long r, long long now, long long num) {
		add[now] = (add[now] + num) % Mod;
		tree[now] = (tree[now] + (r - l + 1) * num % Mod) % Mod;
	}

    void mult_giveMark (long long l, long long r, long long now, long long num) {
		add[now] = add[now] * num % Mod;
        mult[now] = mult[now] * num % Mod;
		tree[now] = tree[now] * num % Mod;
	}
	
	void pushUp (long long now) {
		tree[now] = (tree[lSon (now)] + tree[rSon (now)]) % Mod;
	}
	
	void pushDown (long long l, long long r, long long now) {
		long long m = (l + r) / 2;
		mult_giveMark (l, m, lSon (now), mult[now]);
		add_giveMark (l, m, lSon (now), add[now]);
		mult_giveMark (m + 1, r, rSon (now), mult[now]);
		add_giveMark (m + 1, r, rSon (now), add[now]);
		add[now] = 0;
        mult[now] = 1;
	}
	
	void add_update (long long allL, long long allR, long long nowL, long long nowR, long long now, long long num) {
		if (allL <= nowL && nowR <= allR) {
			add_giveMark (nowL, nowR, now, num);
			return;
		}
 
		pushDown (nowL, nowR, now);
 
		long long m = (nowL + nowR) / 2;
		if (allL <= m) {
			add_update (allL, allR, nowL, m, lSon (now), num);
		}
		if (allR > m) {
			add_update (allL, allR, m + 1, nowR, rSon (now), num);
		}
		pushUp (now);
	}

    void mult_update (long long allL, long long allR, long long nowL, long long nowR, long long now, long long num) {
		if (allL <= nowL && nowR <= allR) {
			mult_giveMark (nowL, nowR, now, num);
			return;
		}
 
		pushDown (nowL, nowR, now);
 
		long long m = (nowL + nowR) / 2;
		if (allL <= m) {
			mult_update (allL, allR, nowL, m, lSon (now), num);
		}
		if (allR > m) {
			mult_update (allL, allR, m + 1, nowR, rSon (now), num);
		}
		pushUp (now);
	}
	
	long long query (long long allL, long long allR, long long nowL, long long nowR, long long now) {
		if (allL <= nowL && nowR <= allR) {
			return tree[now];
		}
 
		long long m = (nowL + nowR) / 2;
		long long res = 0;
		pushDown (nowL, nowR, now);
		if (allL <= m) {
			res = (res + query (allL, allR, nowL, m, lSon (now))) % Mod;
		}
		if (allR > m) {
			res = (res + query (allL, allR, m + 1, nowR, rSon (now))) % Mod;
		}
		return res;
	}
}