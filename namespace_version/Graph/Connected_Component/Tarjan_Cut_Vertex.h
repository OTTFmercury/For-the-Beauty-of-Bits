

#include <cstring>
#include <vector>

const int N = 514;
const int Original_Father = -1;

namespace Tarjan_Cut_Vertex {
    /*
    require:
        class: vector
        constant: N, Original_Father
        function: memset min
        headfile: algorithm cstring vector
    */

    using std::min;
    using std::vector;

    void dfs (vector<int> graph[N], int & n, int dfn[N], int & dfn_cc, int low[N], bool cut_vertex[N], int & cut_vertex_cc, vector<int> & cut_vertexs, int u, int fa) {
        dfn_cc++;
        dfn[u] = low[u] = dfn_cc;

        int children = 0;
        for (auto v : graph[u]) {
            if (!dfn[v]) {
                dfs (graph, n, dfn, dfn_cc, low, cut_vertex, cut_vertex_cc, cut_vertexs, v, u);
                children++;
                low[u] = min (low[u], low[v]);

                if (fa != Original_Father && low[v] >= dfn[u] && !cut_vertex[u]) {
                    cut_vertex[u] = true;
                    cut_vertex_cc++;
                    cut_vertexs.push_back(u);
                }
            }
            else if (fa != v) {
                low[u] = min (low[u], dfn[v]);
            }
        }

        if (fa == Original_Father && children > 1 && !cut_vertex[u]) {
            cut_vertex[u] = true;
            cut_vertex_cc++;
            cut_vertexs.push_back(u);
        }
    }

    void solve (vector<int> graph[N], int & n, int dfn[N], int & dfn_cc, int low[N], bool cut_vertex[N], int & cut_vertex_cc, vector<int> & cut_vertexs) {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                dfs (graph, n, dfn, dfn_cc, low, cut_vertex, cut_vertex_cc, cut_vertexs, i, Original_Father);
            }
        }
    }
}