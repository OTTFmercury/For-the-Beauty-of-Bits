template <typename EdgeT, typename GraphT>
class NetworkFlowWithBound {
	private:
	int n;
	GraphT dif;
	vector<EdgeT> nums;
	EdgeT inf;
	int s;
	int t;
	int S;
	int T;

	public:
	NetworkFlowWithBound (int n, EdgeT inf, int s = 0, int t = 0);

	void add (int u, int v, EdgeT down, EdgeT up);
	EdgeT cal (int st = 1);
};

template <typename EdgeT, typename GraphT>
NetworkFlowWithBound<EdgeT, GraphT>::NetworkFlowWithBound (int n, EdgeT inf, int s, int t) : n (n), dif (n + 10), nums (n + 10), inf (inf), s (s), t (t), S (n + 1), T (n + 2) {
    if (t && s) {
	    add (t, s, 0, inf);
    }
}

template <typename EdgeT, typename GraphT>
void NetworkFlowWithBound<EdgeT, GraphT>::add (int u, int v, EdgeT down, EdgeT up) {
	nums[u] -= down;
	nums[v] += down;
	dif.add(u, v, up - down);
}

template <typename EdgeT, typename GraphT>
EdgeT NetworkFlowWithBound<EdgeT, GraphT>::cal (int st) {
	for (int i = 0; i <= n; i++) {
		if (nums[i] > 0) {
			add(S, i, 0, nums[i]);
		}
		else if (nums[i] < 0) {
			add(i, T, 0, -nums[i]);
		}
	}

	Dinic<EdgeT, GraphT> dinic(dif);

	dinic.dinic(S, T);
	EdgeT res = 0;

    for (auto& [v, w] : dinic.graph[S]) {
		if (w.first) {
            return -1;
        }
	}

	for (auto& [v, w] : dinic.graph[t]) {
		if (v == s) {
			res = dinic.graph[s][w.second].second.first;
			w.first = 0; 
			dinic.graph[s][w.second].second.first = 0;
			break;
		}
	}

    if (st == 1) {
        res += dinic.dinic(s, t);
    }
    if (st == 2) {
        res -= dinic.dinic(t, s);
    }
    
	return res;
}