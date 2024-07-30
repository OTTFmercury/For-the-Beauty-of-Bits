

#include "GraphWithVector.h"

using std::make_pair;

template <typename PointT, typename EdgeT>
class NetworkFlow {
	private:
	PointT n;
	GraphWithVector<PointT, pair<EdgeT, PointT>> nf;

	public:

	NetworkFlow (PointT n = 1e5) : n (n), nf (n) {}
	PointT getN () {return n;}
	void add (PointT u, PointT v, EdgeT w = 1);
	auto& operator [] (const PointT i) {
		return nf[i];
	}
};

template <typename PointT, typename EdgeT>
void NetworkFlow<PointT, EdgeT>::add (PointT u, PointT v, EdgeT w) {
	nf.add(u, v, make_pair (w, nf[v].size()));
	nf.add(v, u, make_pair (0, nf[u].size() - 1));
}