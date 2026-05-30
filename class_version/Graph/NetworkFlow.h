

#include "GraphWithVector.h"

using std::make_pair;

template <typename EdgeT>
class NetworkFlow {
	private:
	int n;
	GraphWithVector<pair<EdgeT, int>> nf;

	public:

	NetworkFlow (int n = 1e5) : n (n), nf (n) {}
	int getN () {return n;}
	void add (int u, int v, EdgeT w = 1);
	auto& operator [] (const int i) {
		return nf[i];
	}
};

template <typename EdgeT>
void NetworkFlow<EdgeT>::add (int u, int v, EdgeT w) {
	nf.add(u, v, make_pair (w, nf[v].size()));
	nf.add(v, u, make_pair (0, nf[u].size() - 1));
}