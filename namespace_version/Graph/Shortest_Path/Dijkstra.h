

#include <queue>
#include <utility>
#include <vector>

const int N = 11451;
const int INF = 1e9;

namespace Dijkstra {
	/*
	require:
		class: pair priority_queue vector
		constant: INF N
		headfile: queue utility vector
	*/

    using std::pair;
    using std::priority_queue;
    using std::vector;
	
	struct Node {
		int id;
		int dis;
		
		Node () = default;
		Node (int id, int dis) : id (id), dis (dis) {}
		
		bool operator< (const Node other) const {
			return dis > other.dis;
		}
	};
	
	void solve (int n, vector<pair<int, int>> graph[N], int s, bool vis[N], int dis[N]) {
		priority_queue<Node> pq;
		for (int i = 1; i <= n; i++) {
			vis[i] = false;
			dis[i] = INF;
		}
		dis[s] = 0;
		pq.emplace(s, 0);
		
		while (!pq.empty()) {
			int u = pq.top().id;
			pq.pop();

            if (vis[u]) {
                continue;
            }
            vis[u] = true;
            
			for (auto [v, w] : graph[u]) {
				if (dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					
					pq.emplace(v, dis[v]);
				}
			}
		}
	}
}