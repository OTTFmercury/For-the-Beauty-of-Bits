
#include <algorithm>
#include <cstring>
#include <queue>

using std::memset;
using std::min;
using std::queue;

template <typename PointT, typename EdgeT, typename GraphT>
class ISAP {
	private:
	
	GraphT graph;
	PointT B;
	PointT E;
	PointT dep[222];
	PointT cc[222];
	PointT cur[222];
	EdgeT res;

	void bfs ();
	EdgeT dfs (PointT now, EdgeT flow);

	public:

	ISAP (GraphT graph) : graph (graph) {}
	EdgeT isap (PointT b, PointT e);
};

template <typename PointT, typename EdgeT, typename GraphT>
void ISAP<PointT, EdgeT, GraphT>::bfs () {
	memset (dep, -1, sizeof (dep));
	cc[0] = 1;
	dep[E] = 0;
	queue<int> q;
	q.push(E);
	
	while (!q.empty()) {
		PointT u = q.front();
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

template <typename PointT, typename EdgeT, typename GraphT>
EdgeT ISAP<PointT, EdgeT, GraphT>::dfs (PointT u, EdgeT flow) {
	if (u == E) {
		return flow;
	}
	
	EdgeT used = 0;
	for (int i = cur[u]; i < int (graph[u].size()); i++) {
		cur[u] = i;
		auto &r = graph[u][i];
		PointT v = r.first;
		EdgeT w = r.second.first;
		PointT another = r.second.second;
		
		if (w && dep[u] - 1 == dep[v]) {
			int num = dfs (v, min (flow - used, w));
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
		dep[B] = graph.getN() + 1;
	}
	dep[u]++;
	cc[dep[u]]++;
	return used;
}

template <typename PointT, typename EdgeT, typename GraphT>
EdgeT ISAP<PointT, EdgeT, GraphT>::isap (PointT b, PointT e) {
	
	res = 0;
	B = b;
	E = e;
	
	bfs ();
	while (dep[B] < graph.getN()) {
		memset (cur, 0, sizeof (cur));
		res += dfs (B, 2147483647);
	}
	
	return res;
}