

#include <algorithm>
#include <cstring>
#include <vector>

const int N = 11451;
const int Original_Father = -1;

namespace Tarjan_Edge_Biconnected_Component {
    /*
    require:
        class: vector
        constant: N
        function: memset min
        headfile: algorithm cstring vector
    */

    using std::min;
    using std::vector;

    void dfs (vector<int> graph[N], int & n, int dfn[N], int & dfn_cc, int low[N], int stack[N], int & stack_top, int belong_to[N], int & ebcc_cc, int ebcc_size[N], int u, int fa) {
        dfn_cc++;
        dfn[u] = low[u] = dfn_cc;

        stack_top++;
        stack[stack_top] = u;

        for (auto v : graph[u]) {
            if (v == fa) {
                continue;
            }

            if (!dfn[v]) {
                dfs (graph, n, dfn, dfn_cc, low, stack, stack_top, belong_to, ebcc_cc, ebcc_size, v, u);
                low[u] = min (low[u], low[v]);
            }
            else {
                low[u] = min (low[u], dfn[v]);
            }
        }

        if (dfn[u] == low[u]) {
            ebcc_cc++;

            while (true) {
                int now = stack[stack_top];

                belong_to[now] = ebcc_cc;
                ebcc_size[ebcc_cc]++;

                stack_top--;
                if (now == u) {
                    break;
                }
            }
        }
    }

    void solve (vector<int> graph[N], int & n, int dfn[N], int & dfn_cc, int low[N], int stack[N], int & stack_top, int belong_to[N], int & ebcc_cc, int ebcc_size[N]) {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                dfs (graph, n, dfn, dfn_cc, low, stack, stack_top, belong_to, ebcc_cc, ebcc_size, i, Original_Father);
            }
        }
    }
}