

#include <algorithm>
#include <array>

using std::array;
using std::swap;

template <typename T, int N>
class LeftTree {
    private:
    int n;
	array<int, N> dist;
	array<int, N> root;
	array<int, N> lc;
	array<int, N> rc;
    int merge (int x, int y);

    public:
    array<T, N> nodes;
    LeftTree () = default;
    LeftTree (int n) : n (n) {
        for (int i = 1; i <= n; i++) {
            root[i] = i;
        }
        dist[0] = -1;
    }

    int find (int num) {return (root[num] == num) ? num : root[num] = find (root[num]);}
    void doMerge (int x, int y) {
        x = find (x);
        y = find (y);
        if (x != y) {
            root[x] = root[y] = merge (x, y);
        }
    }
    void pop (int x) {
        x = find (x);
        root[x] = root[lc[x]] = root[rc[x]] = merge (lc[x], rc[x]);
        lc[x] = rc[x] = dist[x] = 0;
    }
};

template <typename T, int N>
int LeftTree<T, N>::merge (int x, int y) {
    if (x == 0 || y == 0) {
        return x + y;
    }

    if (nodes[x] > nodes[y]) {
        swap (x, y);
    }

    rc[x] = merge (rc[x], y);
    if (dist[lc[x]] < dist[rc[x]]) {
        swap(lc[x], rc[x]);
    }
    dist[x] = dist[rc[x]] + 1;

    return x;
}