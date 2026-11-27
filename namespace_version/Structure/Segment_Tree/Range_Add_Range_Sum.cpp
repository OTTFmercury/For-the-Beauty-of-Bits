

const int N = 100010;

namespace Segment_Tree {
    /*
    require:
        constant: N
    */

	long long tree[N << 2];
	long long mark[N << 2];
	
	long long lSon (long long now) {return now * 2;}
	long long rSon (long long now) {return now * 2 + 1;}
 
	void build (long long l, long long r, long long now, long long nums[N]);
 
	void giveMark (long long l, long long r, long long now, long long num);
 
	void pushUp (long long now);
	void pushDown (long long l, long long r, long long now);
 
	void update (long long allL, long long allR, long long nowL, long long nowR, long long now, long long num);
	long long query (long long allL, long long allR, long long nowL, long long nowR, long long now);
	
	void build (long long l, long long r, long long now, long long nums[N]) {
		mark[now] = 0;
		if (l == r) {
			tree[now] = nums[l];
			return;
		}
 
		long long m = (l + r) / 2;
		build (l, m, lSon (now), nums);
		build (m + 1, r, rSon (now), nums);
		pushUp (now);
	}
	
	void giveMark (long long l, long long r, long long now, long long num) {
		mark[now] = mark[now] + num;
		tree[now] = tree[now] + (r - l + 1) * num;
	}
	
	void pushUp (long long now) {
		tree[now] = tree[lSon (now)] + tree[rSon (now)];
	}
	
	void pushDown (long long l, long long r, long long now) {
		long long m = (l + r) / 2;
		giveMark (l, m, lSon (now), mark[now]);
		giveMark (m + 1, r, rSon (now), mark[now]);
		mark[now] = 0;
	}
	
	void update (long long allL, long long allR, long long nowL, long long nowR, long long now, long long num) {
		if (allL <= nowL && nowR <= allR) {
			giveMark (nowL, nowR, now, num);
			return;
		}
 
		pushDown (nowL, nowR, now);
 
		long long m = (nowL + nowR) / 2;
		if (allL <= m) {
			update (allL, allR, nowL, m, lSon (now), num);
		}
		if (allR > m) {
			update (allL, allR, m + 1, nowR, rSon (now), num);
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
			res = res + query (allL, allR, nowL, m, lSon (now));
		}
		if (allR > m) {
			res = res + query (allL, allR, m + 1, nowR, rSon (now));
		}
		return res;
	}
}