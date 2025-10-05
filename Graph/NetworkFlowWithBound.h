
#include "Dinic.h"

template <typename EdgeT, typename GraphT>
class NetworkFlowWithBound {
	private:
	EdgeT cc = 0;
	int n;
	GraphT dif;
	vector<EdgeT> nums;
	EdgeT inf;
	int s;
	int t;
	int S;
	int T;

	public:
	NetworkFlowWithBound (int n, EdgeT inf, int s = -1, int t = -1);

	void add (int u, int v, EdgeT down, EdgeT up);
	EdgeT cal (int type = 0);
};

template <typename EdgeT, typename GraphT>
NetworkFlowWithBound<EdgeT, GraphT>::NetworkFlowWithBound (int n, EdgeT inf, int s, int t) : n (n), dif (n + 10), nums (n + 10), inf (inf), s (s), t (t), S (n + 1), T (n + 2) {
	assert (0 <= s && s < n && 0 <= t && t < n);
	if (s != -1) {
		add(t, s, 0, inf);
	}
}

template <typename EdgeT, typename GraphT>
void NetworkFlowWithBound<EdgeT, GraphT>::add (int u, int v, EdgeT down, EdgeT up) {
	cc += down;
	nums[u] -= down;
	nums[v] += down;
	dif.add(u, v, up - down);
}

template <typename EdgeT, typename GraphT>
EdgeT NetworkFlowWithBound<EdgeT, GraphT>::cal (int type) {
	for (int i = 0; i <= n; i++) {
		if (nums[i] > 0) {
			add(S, i, 0, nums[i]);
		}
		else {
			add(i, T, nums[i], 0);
		}
	}

	Dinic<EdgeT, GraphT> dinic(dif);
	dinic.dinic(S, T) + cc;
	EdgeT res;

	for (auto& [v, w] : dinic.graph[s]) {
		if (v == t) {
			res = w.first;
			w.first = 0; 
			dinic.graph[t][w.second].second.first = 0;
			break;
		}
	}

	if (type == 1) {
		res += dinic.dinic(s, t);
	}
	if (type == 2) {
		res -= dinic.dinic(t, s);
	}

	return res;
}