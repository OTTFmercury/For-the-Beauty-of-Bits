

#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

using std::pair;
using std::queue;
using std::vector;

template <typename PointT, typename EdgeT, typename GraphT>
class SPFA {
	private:

	GraphT graph;

	public:

	SPFA (GraphT graph) : graph (graph) {}
	vector<EdgeT> spfa (PointT start, EdgeT Inf);
};

template <typename PointT, typename EdgeT, typename GraphT>
vector<EdgeT> SPFA<PointT, EdgeT, GraphT>::spfa (PointT start, EdgeT Inf) {
	vector<EdgeT> res;
	vector<int> judge;
	queue<PointT> q;

	res.resize(graph.getN());
	judge.resize(graph.getN());
	fill (res.begin(), res.end(), Inf);
	fill (judge.begin(), judge.end(), false);
	res[start] = 0;

	q.push(start);

	while (!q.empty()) {
		auto u = q.front();
		q.pop();

		judge[u] = false;

		for (auto [v, w] : graph[u]) {
			if (res[v] > res[u] + w) {
				res[v] = res[u] + w;

				if (!judge[v]) {	
					q.push(v);
					judge[v] = true;
				}
			}
		}
	}

	return res;
}