

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
	vector<int> fail;
	vector<int> inde;
	vector<int> res;
	vector<int> flag;

	vector<int> which;
	vector<int> vis;

	public:
	AhoCorasickAutomaton ();
	void insert (string str);
	void acInit ();
	void ac (string str);
	void topo ();
	auto getWhich () {return which;}
	auto getVis () {return vis;}
};

AhoCorasickAutomaton::AhoCorasickAutomaton () {
	tree.resize(1);
	fail.resize(1);
	inde.resize(1);
	res.resize(1);
	flag.resize(1);

	which.resize(1);
	vis.resize(1);
}

void AhoCorasickAutomaton::insert (string str) {
	int num = 0;
	for (char ch : str) {
		if (!tree[num][(int) ch - 'a']) {
			tree[num][ch - 'a'] = tree.size();
			tree.push_back({});
			fail.push_back(0);
			inde.push_back(0);
			res.push_back(0);
			flag.push_back(0);
		}
		num = tree[num][ch - 'a'];
	}

	if (!flag[num]) {
		flag[num] = which.size();
	}
	which.push_back(flag[num]);
	vis.push_back(0);
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
				inde[fail[tree[u][i]]]++;
				q.push(tree[u][i]);
			}
			else {
				tree[u][i] = tree[fail[u]][i];
			}
		}
	}
}

void AhoCorasickAutomaton::ac (string str) {
	for (int i = 0, j = 0; i < str.size(); i++) {
		j = tree[j][str[i] - 'a'];
		res[j]++;
	}
}

void AhoCorasickAutomaton::topo () {
	queue<int> q;
	for (int i = 1; i < inde.size(); i++) {
		if (!inde[i]) {
			q.push(i);
		}
	}

	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[flag[u]] = res[u];

		int v = fail[u];
		inde[v]--;
		res[v] += res[u];
		if (!inde[v]) {
			q.push(v);
		}
	}
}