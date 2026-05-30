

#include <vector>

using std::vector;

template <typename EdgeT, typename GraphT>
class HLPP {
	private:

	int n;
	GraphT graph;

	public:

	HLPP (GraphT graph) : graph (graph) {
        n = graph.getN();
    }
	EdgeT hlpp (int s, int t);
};

template <typename EdgeT, typename GraphT>
EdgeT HLPP<EdgeT, GraphT>::hlpp (int s, int t) {
    vector<EdgeT> excess(n + 1, 0);
    vector<int> dep (n + 1, n);
    vector<int> gap(2 * n + 1, 0);
    vector<int> curHead (n + 1, 0);
    vector<vector<int>> buckets(2 * n + 1);

    int max_h = 0;
    queue<int> q;
    q.push(t);
    dep[t] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        gap[dep[u]]++;
        for (auto [v, r] : graph[u]) {
			auto [w, another] = r;
			if (dep[v] == n && graph[v][another].second.first > 0) {
                dep[v] = dep[u] + 1;
                q.push(v);
			}
		}
    }

    if (dep[s] == n) {
        return 0;
    }
    dep[s] = n;

    for (auto & [v, r] : graph[s]) {
        auto & [w, another] = r;
        if (w > 0) {
            EdgeT flow = w;
            w -= flow;
            graph[v][another].second.first += flow;
            excess[s] -= flow;
            excess[v] += flow;
        }
        if (v != s && v != t && excess[v] > 0) {
            buckets[dep[v]].push_back(v);
            max_h = max (max_h, dep[v]);
        }
    }

    while (max_h >= 0) {
        if (buckets[max_h].empty()) {
            max_h--;
            continue;
        }

        int u = buckets[max_h].back();
        buckets[max_h].pop_back();
        if (excess[u] == 0 || dep[u] != max_h) {
            continue;
        }

        while (excess[u] > 0) {
            if (dep[u] >= n) {
                excess[u] = 0;
                break;
            }

            if (curHead[u] == graph[u].size()) {
                int min_h = 2 * n;
                for (auto & [v, r] : graph[u]) {
                    auto & [w, another] = r;
                    if (w > 0) {
                        min_h = min (min_h, dep[v]);
                    }
                }

                int old_h = dep[u];
                int new_h = min_h + 1;
                gap[old_h]--;
                dep[u] = new_h;
                gap[new_h]++;

                if (gap[old_h] == 0 && old_h < n) {
                    for (int v = 0; v <= n; v++) {
                        if (v == s || v == t) {
                            continue;
                        }
                        if (dep[v] > old_h && dep[v] < n) {
                            gap[dep[v]]--;
                            dep[v] = n + 1;
                            gap[n + 1]++;
                            if (excess[v] > 0) {
                                buckets[dep[v]].push_back(v);
                            }
                        }
                    }
                }

                max_h = max (max_h, dep[u]);
                curHead[u] = 0;
            }
            else {
                int i = curHead[u];
                auto & [v, r] = graph[u][i];
                auto & [w, another] = r;
                if (w > 0 && dep[u] == dep[v] + 1) {
                    EdgeT flow = min (excess[u], w);
                    w -= flow;
                    graph[v][another].second.first += flow;
                    excess[u] -= flow;
                    excess[v] += flow;

                    if (v != s && v != t && excess[v] > 0) {
                        buckets[dep[v]].push_back(v);
                        max_h = max (max_h, dep[v]);
                    }
                }
                else {
                    curHead[u]++;
                }
            }
        }
    }

    return excess[t];
}