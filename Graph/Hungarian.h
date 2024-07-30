

#include <algorithm>
#include <vector>

using std::fill;
using std::vector;

template <typename PointT, typename EdgeT, typename GraphT>
class Hungarian {
	private:

	PointT n;
	GraphT graph;
	vector<int> judge;
	vector<int> with;

	bool match (PointT u);

	public:

	Hungarian (GraphT graph, PointT n) : graph (graph), n (n) {
		judge.resize(graph.getN());
		with.resize(graph.getN());
	}
	vector<PointT> hungarian ();
};

template <typename PointT, typename EdgeT, typename GraphT>
bool Hungarian<PointT, EdgeT, GraphT>::match (PointT u) {
	for (auto [v, w] : graph[u]) {
        if (!judge[v]) {
            judge[v] = true;
            if (with[v] == 0 || match (with[v])) {
				with[u] = v;
                with[v] = u;
                return true;
            }
        }
    }
    return false;
}

template <typename PointT, typename EdgeT, typename GraphT>
vector<PointT> Hungarian<PointT, EdgeT, GraphT>::hungarian () {
	for (int i = 1; i <= n; i++) {
        fill (judge.begin(), judge.end(), 0);
        match (i);
    }
	return with;
}