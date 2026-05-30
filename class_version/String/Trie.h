

#include <array>
#include <string>
#include <vector>

using std::array;
using std::string;
using std::vector;

class Trie {
	private:
	vector<array<int, 30>> tree;
	vector<int> stop;

	public:
	Trie ();
	void insert (string str);
	int query (string str);
};

Trie::Trie () {
	tree.resize(1);
	stop.resize(1);
}

void Trie::insert (string str) {
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

int Trie::query (string str) {
	int num = 0;
	for (char ch : str) {
		if (!tree[num][ch - 'a']) {
			return false;
		}
		num = tree[num][ch - 'a'];
	}
	return stop[num];
}