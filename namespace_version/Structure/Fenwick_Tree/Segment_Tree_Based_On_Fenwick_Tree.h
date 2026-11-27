

const int N = 100010;

namespace Fenwick_Tree {
    /*
    require:
        constant: N
    */

	inline int lowbit (int id) {
		return (id) & (-id);
	}
	
	void update (int id, long long num, long long tree[N]) {
		for (; id < N; id += lowbit (id)) {
			tree[id] += num;
		}
	}
	
	long long query (int id, long long tree[N]) {
		long long res = 0;
		for (; id > 0; id -= lowbit (id)) {
			res += tree[id];
		}
		return res;
	}
}

namespace Segment_Tree_Based_On_Fenwick_Tree {
    /*
    require:
        constant: N
        namespace: Fenwick_Tree
    */

	long long diff[N];
	long long multi_diff[N];
	
	void range_update (int l, int r, long long num) {
		using Fenwick_Tree::update;
		
		update (l, num, diff);
		update (r + 1, -num, diff);
		update (l, num * (l - 1), multi_diff);
		update (r + 1, -num * r, multi_diff);
	}
	
	long long single_query (int id) {
		using Fenwick_Tree::query;
		
		long long res1 = query (id, diff) * id;
		long long res2 = query (id, multi_diff);
		return res1 - res2;
	}
	
	long long range_query (int l, int r) {
		return single_query (r) - single_query (l - 1);
	}
}