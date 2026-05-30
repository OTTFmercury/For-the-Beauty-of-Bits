

#include <algorithm>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

using std::pair;
using std::priority_queue;
using std::vector;

template <typename PointT, typename EdgeT, typename GraphT>
class Dijkstra {
	private:

	GraphT graph;

	public:

	Dijkstra (GraphT graph) : graph (graph) {}
	vector<EdgeT> dijkstra (PointT start, EdgeT Inf);
};

template <typename PointT, typename EdgeT, typename GraphT>
vector<EdgeT> Dijkstra<PointT, EdgeT, GraphT>::dijkstra (PointT start, EdgeT Inf) {
	using PairT = pair<EdgeT, PointT>;

	vector<EdgeT> res;
	vector<int> judge;
	priority_queue<PairT, vector<PairT>, greater<PairT>> pq;

	res.resize(graph.getN());
	judge.resize(graph.getN());
	fill (res.begin(), res.end(), Inf);
	fill (judge.begin(), judge.end(), false);
	res[start] = 0;

	pq.emplace(0, start);

	while (!pq.empty()) {
		auto u = pq.top().second;
		pq.pop();

		if (judge[u]) {
			continue;
		}
		judge[u] = true;

		for (auto [v, w] : graph[u]) {
			if (res[v] > res[u] + w) {
				res[v] = res[u] + w;

				pq.emplace(res[v], v);
			}
		}
	}

	return res;
}