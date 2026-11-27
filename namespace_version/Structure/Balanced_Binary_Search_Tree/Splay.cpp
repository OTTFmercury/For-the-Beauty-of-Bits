

const int N = 100010;
const int INF = 10000000;

namespace Splay {
    /*
    require:
        constant: N INF
    */

	int son[2][N];
	int * lson = son[0];
	int * rson = son[1];
	int val[N];
	int fa[N];
	int size[N];
	int count[N];
	int tot = 0;
	int root = 0;
	
	void pushup (int id) {
		size[id] = size[lson[id]] + size[rson[id]] + count[id];
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
	
	void find (int & z, int num) {
		int x = z;
		int y = fa[x];
		while (x && (val[x] != num)) {
			y = x;
			x = son[num > val[x]][y];
		}
		if (x) {
			splay (z, x);
		}
		else {
			splay (z, y);
		}
	}
	
	void num_solve (int &z, int rank) {
		int x = z;
		while (true) {
			if (size[lson[x]] >= rank) {
				x = lson[x];
			}
			else if (size[lson[x]] + count[x] >= rank) {
				break;
			}
			else {
				rank -= size[lson[x]] + count[x];
				x = rson[x];
			}
		}
		splay (z, x);
	}
	
	int num (int rank) {
		if (rank > size[root]) {
			return -1;
		}
		num_solve (root, rank);
		return val[root];
	}
	
	int rank (int num) {
		find (root, num);
		return size[lson[root]] + ((val[root] < num) ? count[root] : 0) + 1;
	}
	
	int merge (int x, int y) {
		if (!x || !y) {
			return x | y;
		}
		num_solve (y, 1);
		lson[y] = x;
		fa[x] = y;
		pushup (y);
		return y;
	}
	
	void insert (int num) {
		int x = root;
		int y = 0;
		while (x && (val[x] != num)) {
			y = x;
			x = son[num > val[x]][y];
		}
		
		if (x) {
			count[x]++;
			size[x]++;
		}
		else {
			tot++;
			x = tot;
			val[x] = num;
			count[x] = size[x] = 1;
			fa[x] = y;
			if (y) {
				son[num > val[y]][y] = x;
			}
		}
		
		splay (root, x);
	}
	
	bool remove (int num) {
		find (root, num);
		
		if (!root || (val[root] != num)) {
			return false;
		}
		
		count[root]--;
		size[root]--;
		if (!count[root]) {
			fa[lson[root]] = fa[rson[root]] = 0;
			root = merge (lson[root], rson[root]);
		}
		return true;
	}
	
	int pre (int num) {
		find (root, num);
		if (root && val[root] < num) {
			return val[root];
		}
		
		int x = lson[root];
		if (!x) {
			return -1;
		}
		while (rson[x]) {
			x = rson[x];
		}
		splay (root, x);
		return val[root];
	}
	
	int next (int num) {
		find (root, num);
		if (root && val[root] > num) {
			return val[root];
		}
		
		int x = rson[root];
		if (!x) {
			return -1;
		}
		while (lson[x]) {
			x = lson[x];
		}
		splay (root, x);
		return val[root];
	}
}