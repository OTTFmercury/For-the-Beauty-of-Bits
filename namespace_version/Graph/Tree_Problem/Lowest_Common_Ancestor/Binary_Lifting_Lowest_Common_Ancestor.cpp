

#include <algorithm>
#include <vector>

constexpr int N = 11451;
constexpr int Bit = 15;

namespace Binary_Lifting_Lowest_Common_Ancestor {
    /*
    require:
        class: vector
        constant: Bit N
        function: swap
        headfile: algorithm vector
    */

    using std::swap;
    using std::vector;

    void dfs (vector<int> tree[N], int fa[N][Bit], int depth[N], int u, int dad) {
        fa[u][0] = dad;
        depth[u] = depth[dad] + 1;
        for (int i = 1; i < Bit; i++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }

        for (auto v : tree[u]) {
            if (dad == v) {
                continue;
            }

            dfs (tree, fa, depth, v, u);
        }
    }

    int lca (vector<int> tree[N], int fa[N][Bit], int depth[N], int u, int v) {
        if (depth[u] < depth[v]) {
            swap (u, v);
        }

        for (int i = Bit - 1; i >= 0; i--) {
            if (depth[fa[u][i]] >= depth[v]) {
                u = fa[u][i];
            }
        }

        if (u == v) {
            return u;
        }

        for (int i = Bit - 1; i >= 0; i--) {
            if (fa[u][i] != fa[v][i]) {
                u = fa[u][i];
                v = fa[v][i];
            }
        }

        return fa[u][0];
    }
}