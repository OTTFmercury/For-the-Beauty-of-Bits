

#include <string>
#include <vector>

using std::string;
using std::vector;

template <typename ResT>
class Trie {
	private:
	vector<array<int, 30>> tree;
	vector<ResT> stop;

	public:
	Trie ();
	void insert (string str);
	ResT query (string str);
};

template <typename ResT>
Trie<ResT>::Trie () {
	tree.resize(1);
	stop.resize(1);
}

template <typename ResT>
void Trie<ResT>::insert (string str) {
	int num = 0;
	for (char ch : str) {
		if (!tree[num][ch - 'a']) {
			tree[num][ch - 'a'] = tree.size();
			tree.push_back({});
			stop.push_back(0);
		}
		num = tree[num][ch - 'a'];
	}
	stop[num] = 1 + stop[num];
}

template <typename ResT>
ResT Trie<ResT>::query (string str) {
	int num = 0;
	for (char ch : str) {
		if (!tree[num][ch - 'a']) {
			return false;
		}
		num = tree[num][ch - 'a'];
	}
	return stop[num];
}