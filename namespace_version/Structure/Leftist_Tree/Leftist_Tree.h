

#include <algorithm>

const int N = 114514 << 1;

namespace Leftist_Tree {
    /*
    require:
        function: swap
        headfile: algorithm
    */

    using std::swap;

	struct Node {
		int son[2];
		int fa;
		int dis;
		long long val;
	};
	
	void init (Node tree[N]) {
		tree[0].val = -1;
	}
	
	int & rson (Node tree[N], int x) {
		if (tree[tree[x].son[0]].dis < tree[tree[x].son[1]].dis) {
			return tree[x].son[0];
		}
		return tree[x].son[1];
	}
	
	int merge (Node tree[N], int x, int y) {
		if (!x || !y) {
			return x | y;
		}
		
		if (tree[x].val < tree[y].val) {
			swap (x, y);
		}
		int & rs = rson (tree, x);
		rs = merge (tree, rs, y);
		tree[rs].fa = x;
		tree[x].dis = tree[rson (tree, x)].dis + 1;
		return x;
	}
	
	void pushup (Node tree[N], int x) {
		if (!x) {
			return;
		}
		if (tree[x].dis != tree[rson (tree, x)].dis + 1) {
			tree[x].dis = tree[rson (tree, x)].dis + 1;
			pushup (tree, tree[x].fa);
		}
	}
	
	int erase (Node tree[N], int x) {
		int y = merge (tree, tree[x].son[0], tree[x].son[1]);
		tree[y].fa = tree[x].fa;
		if (tree[tree[x].fa].son[0] == x) {
			tree[tree[x].fa].son[0] = y;
		}
		else if (tree[tree[x].fa].son[1] == x) {
			tree[tree[x].fa].son[1] = y;
		}
		pushup (tree, tree[y].fa);
		return y;
	}
}