

const int N = 100010;

namespace Fenwick_Tree {
    /*
    require:
        constant: N
    */

	int lowbit (int id) {
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

    long long query (int l, int r, long long tree[N]) {
        return query (r, tree) - query (l - 1, tree);
    }
}