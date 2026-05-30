

#include <utility>
#include <vector>

using std::pair;
using std::vector;

template <typename EdgeT>
class GraphWithVector {
	private:
	int n;
	vector<vector<pair<int, EdgeT>>> graph;

	public:

	GraphWithVector (int n = 1e5);
	int getN () {return n;}
	void add (int u, int v, EdgeT w = 1);
	void addBoth (int u, int v, EdgeT w = 1);
	auto& operator [] (const int i) {
		return graph[i];
	}
};

template <typename EdgeT>
GraphWithVector<EdgeT>::GraphWithVector (int n) : n (n) {
	graph.resize(n);
}

template <typename EdgeT>
void GraphWithVector<EdgeT>::add (int u, int v, EdgeT w) {
	graph[u].emplace_back(v, w);
}

template <typename EdgeT>
void GraphWithVector<EdgeT>::addBoth (int u, int v, EdgeT w) {
	add (u, v, w);
	add (v, u, w);
}