

#include <vector>

const int N = 114514;

namespace Kosaraju_Strongly_Connected_Component {
    /*
    require:
        class: vector
        constant: N
        headfile: vector
    */

    using std::vector;

    void dfs1 (vector<int> graph[N], int u, bool vis[N], vector<int> & stack) {
        vis[u] = true;
        for (auto v : graph[u]) {
            if (!vis[v]) {
                dfs1 (graph, v, vis, stack);
            }
        }
        stack.push_back(u);
    }

    void dfs2 (vector<int> graph2[N], int u, bool vis[N], int & scc_cc, int belong[N]) {
        belong[u] = scc_cc;
        vis[u] = true;
        for (auto v : graph2[u]) {
            if (!vis[v]) {
                dfs2 (graph2, v, vis, scc_cc, belong);
            }
        }
    }

    void solve (vector<int> graph[N], vector<int> graph2[N], int n, bool vis[N], vector<int> & stack, int & scc_cc, int belong[N]) {
        for (int i = 1; i <= n; i++) {
            vis[i] = false;
        }
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                dfs1 (graph, i, vis, stack);
            }
        }
        for (int i = 1; i <= n; i++) {
            vis[i] = false;
        }
        scc_cc = 0;
        for (auto it = stack.rbegin(); it != stack.rend(); it++) {
            if (!vis[*it]) {
                scc_cc++;
                dfs2 (graph2, *it, vis, scc_cc, belong);
            }
        }
    }
}