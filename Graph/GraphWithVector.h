

#include <utility>
#include <vector>

using std::pair;
using std::vector;

template <typename PointT, typename EdgeT>
class GraphWithVector {
	private:
	PointT n;
	vector<vector<pair<PointT, EdgeT>>> graph;

	public:

	GraphWithVector (PointT n = 1e5);
	PointT getN () {return n;}
	void add (PointT u, PointT v, EdgeT w = 1);
	void addBoth (PointT u, PointT v, EdgeT w = 1);
	const auto operator [] (const PointT i) const {
		return graph[i];
	}
};

template <typename PointT, typename EdgeT>
GraphWithVector<PointT, EdgeT>::GraphWithVector (PointT n) : n (n) {
	graph.resize(n);
}

template <typename PointT, typename EdgeT>
void GraphWithVector<PointT, EdgeT>::add (PointT u, PointT v, EdgeT w) {
	graph[u].emplace_back(v, w);
}

template <typename PointT, typename EdgeT>
void GraphWithVector<PointT, EdgeT>::addBoth (PointT u, PointT v, EdgeT w) {
	add (u, v, w);
	add (v, u, w);
}