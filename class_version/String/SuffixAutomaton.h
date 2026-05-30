

#include <array>
#include <vector>

using std::array;
using std::vector;

namespace ForSuffixAutomaton {
	struct Node {
		int len;
		array<int, 26> next;
		int link;
	};
}

class SuffixAutomaton {
	private:
	vector<ForSuffixAutomaton::Node> vec;
	int root;
	int last;

	public:
	SuffixAutomaton () : root (1), last (1) {
		vec.resize(2);
	}

	const vector<ForSuffixAutomaton::Node>& getVec () const {
		return vec;
	}

	void insert (char ch);
};

void SuffixAutomaton::insert (char ch) {
	int num = ch - 'a';
	vec.push_back({vec[last].len + 1, 0, 0});
	int u = vec.size() - 1;

	int p = last;
	last = u;
	for (; p && vec[p].next[num] == 0; p = vec[p].link) {
		vec[p].next[num] = u;
	}
	if (!p) {
		vec[u].link = root;
		return;
	}

	int q = vec[p].next[num];
	if (vec[q].len == vec[p].len + 1) {
		vec[u].link = q;
		return;
	}
	
	vec.push_back(vec[q]);
	int clone = vec.size() - 1;
	vec[clone].len = vec[p].len + 1;
	vec[u].link = vec[q].link = clone;
	for (; p && vec[p].next[num] == q; p = vec[p].link) {
		vec[p].next[num] = clone;
	}
	return;
}