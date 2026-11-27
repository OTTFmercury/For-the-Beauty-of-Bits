

#include <queue>
#include <utility>
#include <vector>

const int N = 11451;
const int INF = 1e9;

namespace Shortest_Path_Faster_Algorithm {
	/*
	require:
		class: pair vector
		constant: INF N
		headfile: queue utility vector
	*/
	
    using std::pair;
    using std::queue;
    using std::vector;

	bool solve (int n, vector<pair<int, int>> graph[N], int s, bool vis[N], int dis[N], int cc[N]) {
	    /*
	    detail:
	    	return false for negative loop
	    */
       
		queue<int> q;
		for (int i = 1; i <= n; i++) {
			vis[i] = false;
			dis[i] = INF;
            cc[i] = 0;
		}
		vis[s] = true;
		dis[s] = 0;
		q.push(s);
		cc[s]++;
		
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			vis[u] = false;
			
			for (auto [v, w] : graph[u]) {
				if (dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					cc[v]++;
					if (cc[v] > n) {
						return false;
					}
					
					if (!vis[v]) {
						vis[v] = true;
						q.push(v);
					}
				}
			}
		}
		
		return true;
	}
}