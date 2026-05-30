

#include <array>
#include <string>
#include <tuple>
#include <vector>

using std::array;
using std::make_tuple;
using std::string;
using std::tuple;
using std::vector;

class PalindromicTree {
	private:
	vector<array<int, 30>> tree;
	vector<int> fa;
	vector<int> len;
	vector<int> dep;
	int cc = 0;
	int now = 0;
	string str = " ";

	int fail (int u, int i);

	public:
	PalindromicTree () : tree (2), fa (2), len (2), dep (2) {
		fa[0] = 1;
		len[1] = -1;
	}

	void add (char ch);
	auto res () {
		return make_tuple (fa, len, dep);
	}
};

int PalindromicTree::fail (int u, int i) {
	while (i - len[u] - 1 <= 0 || str[i - len[u] - 1] != str[i]) {
		u = fa[u];
	}
	return u;
}

void PalindromicTree::add (char ch) {
	cc++;
	str += ch;
	int pos = fail (now, cc);
	int num = ch - 'a';
	if (!tree[pos][num]) {
		tree.push_back({});
		fa.push_back({});
		len.push_back({});
		dep.push_back({});
		
		*fa.rbegin() = tree[fail (fa[pos], cc)][num];
		tree[pos][num] = tree.size() - 1;
		*len.rbegin() = len[pos] + 2;

		*dep.rbegin() = dep[*fa.rbegin()] + 1;
	}
	now = tree[pos][num];
}