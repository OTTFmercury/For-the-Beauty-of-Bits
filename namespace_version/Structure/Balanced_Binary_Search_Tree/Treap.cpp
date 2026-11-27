

#include <ctime>
#include <random>

using namespace std;

const int N = 100010;
const int INF = 10000000;
namespace Treap {
    /*
    require:
		funcction : time
		head file : ctime random
        constant : INF N
    */

	default_random_engine e(time(0));
	uniform_int_distribution<int> u(1, INF);
	inline int rand () {
		return u (e);
	}
	
	int son[2][N];
	int * lson = son[0];
	int * rson = son[1];
	int val[N];
	int priority[N];
	int size[N];
	int count[N];
	int tot = 0;
	int root = 0;
	
	int new_node (int num) {
		tot++;
		val[tot] = num;
		priority[tot] = rand ();
		size[tot] = 1;
		count[tot] = 1;
		return tot;
	}
	
	void pushup (int id) {
		size[id] = size[lson[id]] + size[rson[id]] + count[id];
	}
	
	void build () {
		root = new_node (-INF);
		rson[root] = new_node (INF);
		pushup (root);
	}
	
	enum direction : int {left = 0, right = 1};
	// C++ : enum -> int ok, int -> enum not ok
	// I : angry
	void rotate (int & id, direction d) {
		int t = son[d ^ 1][id];
		son[d ^ 1][id] = son[d][t];
		son[d][t] = id;
		id = t;
		pushup (son[d][id]);
		pushup (id);
	}
	
	void insert_solve (int & id, int num) {
		if (!id) {
			id = new_node (num);
			return;
		}
		
		if (num == val[id]) {
			count[id]++;
		}
		else {
			direction d = ((num < val[id]) ? left : right);
			insert_solve (son[d][id], num);
			
			if (priority[id] < priority[son[d][id]]) {
				rotate (id, direction (d ^ 1));
			}
		}
		
		pushup (id);
	}
	
	void insert (int num) {
		insert_solve (root, num);
	}
	
	void remove_solve (int & id, int num) {
		if (!id) {
			return;
		}
		
		if (num == val[id]) {
			if (count[id] > 1) {
				count[id]--;
				pushup (id);
				return;
			}
			
			if (lson[id] || rson[id]) {
				direction d;
				if (!rson[id] || (priority[lson[id]] > priority[rson[id]])) {
					d = left;
				}
				else {
					d = right;
				}
				rotate (id, direction (d ^ 1));
				remove_solve (son[d ^ 1][id], num);
				pushup (id);
			}
			else {
				id = 0;
			}
			return;
		}
		
		if (num < val[id]) {
			remove_solve (lson[id], num);
		}
		else {
			remove_solve (rson[id], num);
		}
		
		pushup (id);
	}
	
	void remove (int num) {
		remove_solve (root, num);
	}
	
	int rank_solve (int id, int num) {
		if (!id) {
			return 1;
		}
		
		if (num < val[id]) {
			return rank_solve (lson[id], num);
		}
		if (num == val[id]) {
			return size[lson[id]] + 1;
		}
		return size[lson[id]] + count[id] + rank_solve (rson[id], num);
	}
	
	int rank (int num) {
		return rank_solve (root, num) - 1;
	}
	
	int num_solve (int id, int rank) {
		if (!id) {
			return INF;
		}
		
		if (rank <= size[lson[id]]) {
			return num_solve (lson[id], rank);
		}
		if (rank <= size[lson[id]] + count[id]) {
			return val[id];
		}
		return num_solve (rson[id], rank - size[lson[id]] - count[id]);
	}
	
	int num (int rank) {
		return num_solve (root, rank + 1);
	}
	
	int pre (int num) {
    	int id = root;
    	int ans;
    	while (id) {
        	if (val[id] < num) {
            	ans = val[id];
            	id = rson[id];
        	} 
			else {
            	id = lson[id];
        	}
    	}
    	return ans;
	}
	
	int next (int num) {
    	int id = root;
    	int ans;
    	while (id) {
        	if (val[id] > num) {
            	ans = val[id];
            	id = lson[id];
        	} 
			else {
            	id = rson[id];
        	}
    	}
    	return ans;
	}
}