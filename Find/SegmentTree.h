

#include <vector>

using std::vector;

template <typename ResT, ResT (*FunCal) (ResT one, ResT two)>
class SegmentTree {
	private:
	int n;
	vector<ResT> nums;
	vector<ResT> tree;
	vector<ResT> mark;

	long long lSon (long long now) {return now * 2;}
	long long rSon (long long now) {return now * 2 + 1;}

	void build (long long l, long long r, long long now);

	void giveMark (long long l, long long r, long long now, ResT num);

	void pushUp (long long now);
	void pushDown (long long l, long long r, long long now);

	void update (long long allL, long long allR, long long nowL, long long nowR, long long now, ResT num);
	ResT query (long long allL, long long allR, long long nowL, long long nowR, long long now);

	public:
	SegmentTree () = default;
	SegmentTree (vector<ResT> nums);

	void update (long long allL, long long allR, ResT num) {update (allL, allR, 1, n, 1, num);}
	ResT query (long long allL, long long allR) {return query (allL, allR, 1, n, 1);}

};

template <typename ResT, ResT (*FunCal) (ResT one, ResT two)>
void SegmentTree<ResT, FunCal>::build (long long l, long long r, long long now) {
	mark[now] = 0;
	if (l == r) {
		tree[now] = nums[l];
		return;
	}

	long long m = (l + r) / 2;
	build (l, m, lSon (now));
	build (m + 1, r, rSon (now));
	pushUp (now);
}

template <typename ResT, ResT (*FunCal) (ResT one, ResT two)>
void SegmentTree<ResT, FunCal>::giveMark (long long l, long long r, long long now, ResT num) {
	mark[now] = FunCal (mark[now], num);
	tree[now] = FunCal (tree[now], (r - l + 1) * num);
}

template <typename ResT, ResT (*FunCal) (ResT one, ResT two)>
void SegmentTree<ResT, FunCal>::pushUp (long long now) {
	tree[now] = FunCal (tree[lSon (now)], tree[rSon (now)]);
}

template <typename ResT, ResT (*FunCal) (ResT one, ResT two)>
void SegmentTree<ResT, FunCal>::pushDown (long long l, long long r, long long now) {
	long long m = (l + r) / 2;
	giveMark (l, m, lSon (now), mark[now]);
	giveMark (m + 1, r, rSon (now), mark[now]);
	mark[now] = 0;
}

template <typename ResT, ResT (*FunCal) (ResT one, ResT two)>
SegmentTree<ResT, FunCal>::SegmentTree (vector<ResT> nums) : nums (nums), n (nums.size() - 1) {
	tree.resize(n * 4);
	mark.resize(n * 4);

	build (1, n, 1);
}	

template <typename ResT, ResT (*FunCal) (ResT one, ResT two)>
void SegmentTree<ResT, FunCal>::update (long long allL, long long allR, long long nowL, long long nowR, long long now, ResT num) {
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

template <typename ResT, ResT (*FunCal) (ResT one, ResT two)>
ResT SegmentTree<ResT, FunCal>::query (long long allL, long long allR, long long nowL, long long nowR, long long now) {
	if (allL <= nowL && nowR <= allR) {
		return tree[now];
	}

	long long m = (nowL + nowR) / 2;
	long long res = 0;
	pushDown (nowL, nowR, now);
	if (allL <= m) {
		res = FunCal (res, query (allL, allR, nowL, m, lSon (now)));
	}
	if (allR > m) {
		res = FunCal (res, query (allL, allR, m + 1, nowR, rSon (now)));
	}
	return res;
}