

#include <algorithm>
#include <cstring>
#include <vector>

const int N = 114514;

namespace Tarjan_Strongly_Connected_Component {
    /*
    require:
        class: vector
        constant: N
        function: memset min
        headfile: algorithm cstring vector
    */

    using std::min;
    using std::vector;

    void dfs (vector<int> graph[N], int & n, int dfn[N], int & dfn_cc, int low[N], int stack[N], int & stack_top, bool in_stack[N], int belong_to[N], int & scc_cc, int scc_size[N], int u) {
        dfn_cc++;
        dfn[u] = low[u] = dfn_cc;

        stack_top++;
        stack[stack_top] = u;
        in_stack[u] = true;

        for (auto v : graph[u]) {
            if (!dfn[v]) {
                dfs (graph, n, dfn, dfn_cc, low, stack, stack_top, in_stack, belong_to, scc_cc, scc_size, v);
                low[u] = min (low[u], low[v]);
            }
            else if (in_stack[v]) {
                low[u] = min (low[u], dfn[v]);
            }
        }

        if (dfn[u] == low[u]) {
            scc_cc++;

            while (true) {
                int now = stack[stack_top];

                belong_to[now] = scc_cc;
                scc_size[scc_cc]++;
                in_stack[now] = false;

                stack_top--;
                if (now == u) {
                    break;
                }
            }
        }
    }

    void solve (vector<int> graph[N], int & n, int dfn[N], int & dfn_cc, int low[N], int stack[N], int & stack_top, bool in_stack[N], int belong_to[N], int & scc_cc, int scc_size[N]) {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                dfs (graph, n, dfn, dfn_cc, low, stack, stack_top, in_stack, belong_to, scc_cc, scc_size, i);
            }
        }
    }
}