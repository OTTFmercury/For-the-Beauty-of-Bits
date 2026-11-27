

#include <algorithm>
#include <iostream>
#include <functional>

const int N = 100010;
const int INF = 100010;

using std::cout;
using std::function;
using std::swap;

namespace Splay_Range {
    /*
    require:
        constant:  INF
        function: swap
        head file: algorithm iostream funcitonal
        object: cout
        template class: function
    */

	int son[2][N];
	int * lson = son[0];
	int * rson = son[1];
	int val[N];
	int fa[N];
	int size[N];
	bool lazy[N];
	int tot = 0;
	int root = 0;
	
	void pushup (int id) {
		size[id] = size[lson[id]] + size[rson[id]] + 1;
	}
	
	void lazy_reverse (int id) {
		swap (lson[id], rson[id]);
		lazy[id] ^= 1;
	}
	
	void pushdown (int id) {
		if (lazy[id]) {
			if (lson[id]) {
				lazy_reverse (lson[id]);
			}
			if (rson[id]) {
				lazy_reverse (rson[id]);
			}
			lazy[id] = false;
		}
	}
	
	enum direction : int {left = 0, right = 1};
	// C++ : enum -> int ok, int -> enum not ok
	// I : angry
	direction dir (int id) {
		return direction (id == rson[fa[id]]);
	}
	
	void rotate (int x) {
		int y = fa[x];
		int z = fa[y];
		direction d = dir (x);
		
		son[d][y] = son[!d][x];
		son[!d][x] = y;
		if (z) {
			son[dir (y)][z] = x;
		}
		if (son[d][y]) {
			fa[son[d][y]] = y;
		}
		fa[y] = x;
		fa[x] = z;
		pushup (y);
		pushup (x);
	}
	
	void splay (int & z, int x) {
		int w = fa[z];
		for (int y; y = fa[x], y != w; rotate(x)) {
			if (fa[y] != w) {
				if (dir (x) == dir (y)) {
					rotate (y);
				}
				else {
					rotate (x);
				}
			}
		}
		z = x;
	}
	
	void build (int & now, int father, int l, int r, function <int (int)> arr) {
		/*
		require:
			arr (0) = -INF
			arr (n + 1) = INF
		*/
		
		if (l > r) {
			return;
		}
		
		tot++;
		now = tot;
		int mid = (l + r) / 2;
		
		val[now] = arr (mid);
		fa[now] = father;
		size[now] = 1;
		
		if (l < r) {
			build (lson[now], now, l, mid - 1, arr);
			build (rson[now], now, mid + 1, r, arr);
			pushup (now);
		}
	}
	
	void num_solve (int &z, int rank) {
		int x = z;
		pushdown (x);
		while (true) {
			if (size[lson[x]] >= rank) {
				x = lson[x];
			}
			else if (size[lson[x]] + 1 == rank) {
				break;
			}
			else {
				rank -= size[lson[x]] + 1;
				x = rson[x];
			}
			pushdown (x);
		}
		splay (z, x);
	}
	
	void reverse (int l, int r) {
		num_solve (root, l);
		num_solve (rson[root], r - l + 2);
		
		int x = lson[rson[root]];
		lazy_reverse (x);
		pushdown (x);
		splay (root, x);
	}
	
	void display (int now) {
		if (!now) {
			return;
		}
		pushdown (now);
		display (lson[now]);
		cout << val[now] << ' ';
		display (rson[now]);
	}
	
	void display () {
		num_solve (root, 1);
		num_solve (rson[root], size[root] - 1);
		display (lson[rson[root]]);
	}
}