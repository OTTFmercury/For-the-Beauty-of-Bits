
#include <queue>
#include <utility>

using std::pair;
using std::queue;

template <typename PointT, typename EdgeT>
class NetworkFlowWithCost {
	private:
	PointT n;
	GraphWithVector<PointT, tuple<EdgeT, EdgeT, PointT>> nf;

	public:

	NetworkFlowWithCost (PointT n = 1e5) : n (n), nf (n) {}
	PointT getN () {return n;}
	void add (PointT u, PointT v, EdgeT w = 1, EdgeT c = 1);
	auto& operator [] (const PointT i) {
		return nf[i];
	}
};

template <typename PointT, typename EdgeT>
void NetworkFlowWithCost<PointT, EdgeT>::add (PointT u, PointT v, EdgeT w, EdgeT c) {
	nf.add(u, v, make_tuple (w, c, nf[v].size()));
	nf.add(v, u, make_tuple (0, -c, nf[u].size() - 1));
}

template <typename PointT, typename EdgeT, typename GraphT>
class SuccessiveShortestPath {
	private:

	GraphT graph;
	PointT B;
	PointT E;
	vector<int> dep;
	vector<int> cur;
	vector<int> vis;
	EdgeT res;
	EdgeT cost;

	bool spfa ();
	EdgeT dfs (PointT now, EdgeT limit);

	public:

	SuccessiveShortestPath (GraphT graph) : graph (graph) {
		dep.resize(graph.getN() + 2);
		cur.resize(graph.getN() + 2);
		vis.resize(graph.getN() + 2);
	}
	pair<EdgeT, EdgeT> ssp (PointT b, PointT e);
};

template <typename PointT, typename EdgeT, typename GraphT>
bool SuccessiveShortestPath<PointT, EdgeT, GraphT>::spfa () {
	fill (dep.begin(), dep.end(), 1e9);
	fill (cur.begin(), cur.end(), 0);
	fill (vis.begin(), vis.end(), 0);
	
	queue<PointT> q;
	q.push(B);
	dep[B] = 0;
	vis[B] = true;
	
	while (!q.empty()) {
		PointT u = q.front();
		q.pop();
		vis[u] = false;
		
		for (auto [v, ww] : graph[u]) {
			auto [w, c, another] = ww;
			if ((dep[v] == 1e9 || dep[v] > dep[u] + c) && w != 0) {
				dep[v] = dep[u] + c;
				if (!vis[v]) {
					q.push(v);
					vis[v] = true;
				}
			}
		}
	}
	
	return (dep[E] != 1e9);
}

template <typename PointT, typename EdgeT, typename GraphT>
EdgeT SuccessiveShortestPath<PointT, EdgeT, GraphT>::dfs (PointT now, EdgeT limit) {
	if (now == E) {
		return limit;
	}
	
	vis[now] = true;
	for (int i = cur[now]; i < graph[now].size(); i++) {
		cur[now] = i;

		PointT u = now;
		auto& [v, ww] = graph[u][i];
		auto& [w, c, another] = ww;
		
		if (!vis[v] && dep[u] + c == dep[v] && w != 0) {
			EdgeT t = dfs (v, min (w, limit));
			
			if (t) {
				get<0> (graph[u][i].second) -= t;
				get<0> (graph[v][another].second) += t;
				cost += c * t;
				return t;
			}
			else {
				dep[v] = 1e9;
			}
		}
	}
	vis[now] = false;
	
	return 0;
}

template <typename PointT, typename EdgeT, typename GraphT>
pair<EdgeT, EdgeT> SuccessiveShortestPath<PointT, EdgeT, GraphT>::ssp (PointT b, PointT e) {
	
	res = 0;
	cost = 0;
	B = b;
	E = e;

	EdgeT flow = 0;
	while (spfa ()) {
		while (flow = dfs (B, 1e9)) {
			res += flow;
		}
	}
	
	return make_pair (res, cost);
}