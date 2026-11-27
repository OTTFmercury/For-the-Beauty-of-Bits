

#include <array>

const int N = 514514 << 1;
const int AlphabetSize = 26;

namespace Suffix_Automaton {
	/*  
    require:
        constant: N, AlphabetSize
        headfile: array
        template: array
    */
    
    using std::array;

    struct Node {
		int len;
		array<int, AlphabetSize> next;
		int link;
	};
    
    void init (int & root, int & last, int & tot) {
    	tot = 1;
    	root = 1;
    	last = 1;
	}
	
	void insert (Node tree[N], int & root, int & last, int & tot, char ch) {
		int num = ch - 'a';
		tot++;
		tree[tot] = {tree[last].len + 1, 0, 0};
		int u = tot;

		int p = last;
		last = u;
		for (; p && tree[p].next[num] == 0; p = tree[p].link) {
			tree[p].next[num] = u;
		}
		if (!p) {
			tree[u].link = root;
			return;
		}

		int q = tree[p].next[num];
		if (tree[q].len == tree[p].len + 1) {
			tree[u].link = q;
			return;
		}
		
		tot++;
		tree[tot] = tree[q];
		int clone = tot;
		tree[clone].len = tree[p].len + 1;
		tree[u].link = tree[q].link = clone;
		for (; p && tree[p].next[num] == q; p = tree[p].link) {
			tree[p].next[num] = clone;
		}
	}
}