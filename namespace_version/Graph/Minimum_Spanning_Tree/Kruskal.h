constexpr int Size = 233;

namespace Union_Find {
    /*
    require:
        constant: Size
    */

    void init (int dad[Size], int size[Size], int n) {
        for (int i = 1; i <= n; i++) {
            dad[i] = i;
            size[i] = 1;
        }
    }

    int find (int dad[Size], int id) {
        if (dad[id] == id) {
            return id;
        }

        dad[id] = find (dad, dad[id]);
        return dad[id];
    }

    void merge (int dad[Size], int size[Size], int one, int two) {
        one = find (dad, one);
        two = find (dad, two);

        if (one == two) {
            return;
        }

        if (size[one] < size[two]) {
            dad[one] = two;
            size[two] += size[one];
        }
        else {
            dad[two] = one;
            size[one] += size[two];
        }
    }

    bool same (int dad[Size], int one, int two) {
        return find (dad, one) == find (dad, two);
    }
}

#include <algorithm>
#include <vector>

constexpr int N = 233;

namespace Kruskal {
    /*
    require:
        class: algorithm vector
        constant: N
        function: sort
        headfile: vector
    */

    using std::sort;
    using std::vector;

    struct Road {
        int u;
        int v;
        int w;
        Road () = default;
        Road (int u, int v, int w) : u (u), v (v), w (w) {}

        bool operator< (Road other) {
            return w < other.w;
        }
    };

    int solve (vector<Road> & roads, int n, int dad[Size], int size[Size]) {
        /*
        details:
            return -1 for being no mst
        */

        sort (roads.begin(), roads.end());

        Union_Find::init (dad, size, n);

        int cc = 0;
        int res = 0;

        for (auto [u, v, w] : roads) {
            if (Union_Find::same (dad, u, v)) {
                continue;
            }

            Union_Find::merge (dad, size, u, v);
            res += w;
            cc++;

            if (cc == n - 1) {
                break;
            }
        }

        if (cc < n - 1) {
            return -1;
        }

        return res;
    }
}