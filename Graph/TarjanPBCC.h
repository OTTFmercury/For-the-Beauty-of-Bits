#include <stack>
#include <vector>
#include "GraphWithVector.h"

using std::vector;

template <typename PointT, typename EdgeT, typename GraphT>
class TarjanPBCC {
	private:
	
	GraphT graph;
	int cc;
	vector<int> dfn;
	vector<int> low;
	stack<PointT> s;
	vector<vector<PointT>> nums;
	
	void dfs (PointT now, PointT dad);

	public:
	
	TarjanPBCC (GraphT graph);
	vector<vector<PointT>> tarjanPBCC ();
};

template <typename PointT, typename EdgeT, typename GraphT>
TarjanPBCC<PointT, EdgeT, GraphT>::TarjanPBCC (GraphT graph) : graph (graph) {
	dfn.resize(graph.getN());
	low.resize(graph.getN());
	nums.resize(graph.getN());
}

template <typename PointT, typename EdgeT, typename GraphT>
void TarjanPBCC<PointT, EdgeT, GraphT>::dfs (PointT now, PointT dad) {
	cc++;
	dfn[now] = low[now] = cc;
	
	if (!dad && graph[now].empty()) {
		res++;
		nums[res].push_back(now);
		return;
	}
	
	s.push(now);
	
	for (auto son : graph[now]) {
		if (!dfn[son]) {
			dfs (son, now);
			
			low[now] = min (low[now], low[son]);
			
			if (low[son] >= dfn[now]) {
				res++;
				int p = 0;
				
				while (p != son) {
					p = s.top();
					s.pop();
					nums[res].push_back(p);
				}
				nums[res].push_back(now);
			}
		}
		else {
			low[now] = min (low[now], dfn[son]);
		}
	}
}

template <typename PointT, typename EdgeT, typename GraphT>
vector<vector<PointT>> TarjanPBCC<PointT, EdgeT, GraphT>::tarjanPBCC () {
	for (int i = 1; i <= n; i++) {
		if (!dfn[i]) {
			dfs (i, 0);
		}
	}

	return nums;
}