
#include <algorithm>
#include <cstring>
#include <queue>

using std::fill;
using std::memset;
using std::min;
using std::queue;

template <typename PointT, typename EdgeT, typename GraphT>
class Dinic {
	private:

	GraphT graph;
	PointT B;
	PointT E;
	PointT dep[211];
	PointT cur[211];
	EdgeT res;

	bool bfs ();
	EdgeT dfs (PointT now, EdgeT limit);

	public:

	Dinic (GraphT graph) : graph (graph) {}
	EdgeT dinic (PointT b, PointT e);
};

template <typename PointT, typename EdgeT, typename GraphT>
bool Dinic<PointT, EdgeT, GraphT>::bfs () {
	memset (dep, -1, sizeof (dep));
	memset (cur, 0, sizeof (cur));
	
	queue<PointT> q;
	q.push(B);
	dep[B] = 0;
	
	while (!q.empty()) {
		PointT u = q.front();
		q.pop();
		
		for (auto [v, ww] : graph[u]) {
			auto [w, another] = ww;
			if (dep[v] == -1 && w != 0) {
				dep[v] = dep[u] + 1;
				q.push(v);
			}
		}
	}
	
	return (dep[E] != -1);
}

template <typename PointT, typename EdgeT, typename GraphT>
EdgeT Dinic<PointT, EdgeT, GraphT>::dfs (PointT now, EdgeT limit) {
	if (now == E) {
		return limit;
	}
	
	for (int i = cur[now]; i < graph[now].size(); i++) {
		cur[now] = i;

		PointT u = now;
		auto [v, ww] = graph[u][i];
		auto [w, another] = ww;
		
		if (dep[u] + 1 == dep[v] && graph[u][i].second.first != 0) {
			EdgeT t = dfs (v, min (w, limit));
			
			if (t) {
				graph[u][i].second.first -= t;
				graph[v][another].second.first += t;
				return t;
			}
			else {
				dep[v] = -1;
			}
		}
	}
	
	return 0;
}

template <typename PointT, typename EdgeT, typename GraphT>
EdgeT Dinic<PointT, EdgeT, GraphT>::dinic (PointT b, PointT e) {
	
	res = 0;
	B = b;
	E = e;

	EdgeT flow = 0;
	while (bfs ()) {
		while (flow = dfs (B, 1e9)) {
			res += flow;
		}
	}
	
	return res;
}