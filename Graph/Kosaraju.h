

#include <vector>
#include "GraphWithVector.h"

using std::vector;

template <typename PointT, typename EdgeT, typename GraphT>
class Kosaraju {
	private:
	
	GraphT graph;
	GraphT another;
	vector<char> vis;
	vector<PointT> nums;
	int cc = 0;
	vector<PointT> color;
	
	void dfs1 (int now);
	void dfs2 (int now);
	
	public:
	
	Kosaraju (GraphT graph);
	vector<PointT> kosaraju ();
};

template <typename PointT, typename EdgeT, typename GraphT>
Kosaraju<PointT, EdgeT, GraphT>::Kosaraju (GraphT graph) : graph (graph) {
	vis.resize(graph.getN());
	nums.resize(graph.getN());
	color.resize(graph.getN());
	
	for (PointT u = 0; u < graph.getN(); u++) {
		for (auto v : graph[u]) {
			another.add(v.first, u);
		}
	}
}

template <typename PointT, typename EdgeT, typename GraphT>
void Kosaraju<PointT, EdgeT, GraphT>::dfs1 (int now) {
	vis[now] = true;
	for (auto son : graph[now]) {
		if (!vis[son.first]) {
			dfs1 (son.first);
		}
	}
	nums.push_back(now);
}

template <typename PointT, typename EdgeT, typename GraphT>
void Kosaraju<PointT, EdgeT, GraphT>::dfs2 (int now) {
	color[now] = cc;
	for (auto son : another[now]) {
		if (!color[son.first]) {
			dfs2 (son.first);
		}
	}
}

template <typename PointT, typename EdgeT, typename GraphT>
vector<PointT> Kosaraju<PointT, EdgeT, GraphT>::kosaraju () {
	for (PointT i = 0; i < graph.getN(); i++) {
		if (!vis[i]) {
			dfs1 (i);
		}
	}
	for (auto it = nums.rbegin(); it != nums.rend(); it++) {
		if (!color[*it]) {
			cc++;
			dfs2 (*it);
		}
	}
	return color;
}