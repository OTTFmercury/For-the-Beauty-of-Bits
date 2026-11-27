
#include <queue>
#include <utility>
#include <vector>

constexpr int N = 5145;
constexpr int INF = 1e9;

namespace Prim {
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
	
	int solve (int n, vector<pair<int, int>> graph[N], bool vis[N], int dis[N]) {
		priority_queue<Node> pq;
		for (int i = 1; i <= n; i++) {
			vis[i] = false;
			dis[i] = INF;
		}
		dis[1] = 0;
		pq.emplace(1, 0);
		
		int cc = 0;
		int ans = 0;
		while (!pq.empty()) {
		    if (cc == n) {
		        break;
            }
            
			int u = pq.top().id;
			pq.pop();
			
			if (vis[u]) {
			    continue;
            }
            vis[u] = true;
			
			cc++;
			ans += dis[u];
			
			for (auto [v, w] : graph[u]) {
				if (dis[v] > w) {
					dis[v] = w;
					
					pq.emplace(v, dis[v]);
				}
			}
		}
		return ans;
	}
}