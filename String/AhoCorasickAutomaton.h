

#include <array>
#include <string>
#include <utility>
#include <vector>
#include <queue>

using std::array;
using std::pair;
using std::queue;
using std::string;
using std::vector;

class AhoCorasickAutomaton {
	private:
	vector<array<int, 30>> tree;
	vector<int> stop;
	vector<int> which;
	vector<int> fail;
	int cc = 0;

	public:
	AhoCorasickAutomaton ();
	void insert (string str);
	void acInit ();
	vector<int> ac (string str);
};

AhoCorasickAutomaton::AhoCorasickAutomaton () {
	tree.resize(1);
	stop.resize(1);
	which.resize(1);
	fail.resize(1);
}

void AhoCorasickAutomaton::insert (string str) {
	int num = 0;
	for (char ch : str) {
		if (!tree[num][(int) ch - 'a']) {
			tree[num][ch - 'a'] = tree.size();
			tree.push_back({});
			stop.push_back(0);
			which.push_back(0);
			fail.push_back(0);
		}
		num = tree[num][ch - 'a'];
	}
	stop[num] = 1 + stop[num];
	which[num] = ++cc;
}

void AhoCorasickAutomaton::acInit () {
	queue<int> q;
	for (int i = 0; i < 26; i++) {
		if (tree[0][i]) {
			fail[tree[0][i]] = 0;
			q.push(tree[0][i]);
		}
	}
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = 0; i < 26; i++) {
			if (tree[u][i]) {
				fail[tree[u][i]] = tree[fail[u]][i];
				q.push(tree[u][i]);
			}
			else {
				tree[u][i] = tree[fail[u]][i];
			}
		}
	}
}

vector<int> AhoCorasickAutomaton::ac (string str) {
	vector<int> res;
	res.resize(cc + 1);

	for (int i = 0, j = 0; i < str.size(); i++) {
		j = tree[j][str[i] - 'a'];
		for (int t = j; t; t = fail[t]) {
			res[which[t]]++;
		}
	}

	return res;
}