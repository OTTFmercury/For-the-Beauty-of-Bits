
#include <algorithm>
#include <cstring>
#include <queue>

using std::memset;
using std::min;
using std::queue;

template <typename EdgeT, typename GraphT>
class ISAP {
	private:
	
	int B;
	int E;
	vector<int> dep;
	vector<int> cc;
	vector<int> cur;
	EdgeT res;

	void bfs ();
	EdgeT dfs (int now, EdgeT flow);

	public:

	GraphT graph;

	ISAP (GraphT graph) : graph (graph) {
		dep.resize(graph.getN() + 2);
		cc.resize(graph.getN() + 2);
		cur.resize(graph.getN() + 2);
	}
	EdgeT isap (int b, int e);
};

template <typename EdgeT, typename GraphT>
void ISAP<EdgeT, GraphT>::bfs () {
	fill (dep.begin(), dep.end(), -1);
	cc[0] = 1;
	dep[E] = 0;
	queue<int> q;
	q.push(E);
	
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		
		for (auto r : graph[u]) {
			int v = r.first;
			if (dep[v] != -1) {
				continue;
			}
			
			q.push(v);
			dep[v] = dep[u] + 1;
			cc[dep[v]]++;
		}
	}
}

template <typename EdgeT, typename GraphT>
EdgeT ISAP<EdgeT, GraphT>::dfs (int u, EdgeT flow) {
	if (u == E) {
		return flow;
	}
	
	EdgeT used = 0;
	for (int i = cur[u]; i < int (graph[u].size()); i++) {
		cur[u] = i;
		auto &r = graph[u][i];
		int v = r.first;
		EdgeT w = r.second.first;
		int another = r.second.second;
		
		if (w && dep[u] - 1 == dep[v]) {
			EdgeT num = dfs (v, min (flow - used, w));
			if (num) {
				r.second.first -= num;
				graph[v][another].second.first += num;
				used += num;
			}
		}
		
		if (used == flow) {
			return used;
		}
	}
	
	cc[dep[u]]--;
	if (cc[dep[u]] == 0) {
		dep[B] = graph.getN();
	}
	dep[u]++;
	cc[dep[u]]++;
	return used;
}

template <typename EdgeT, typename GraphT>
EdgeT ISAP<EdgeT, GraphT>::isap (int b, int e) {
	
	res = 0;
	B = b;
	E = e;
	
	bfs ();
	while (dep[B] < graph.getN()) {
		fill (cur.begin(), cur.end(), 0);
		res += dfs (B, 2147483647);
	}
	
	return res;
}