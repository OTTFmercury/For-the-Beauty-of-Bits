

#include <algorithm>

const int N = 114;

namespace Floyd {
    /*
    require:
        constant: N
        function: min
        headfile: algorithm
    */

    using std::min;

    void solve (int dis[N][N], int n) {
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    dis[i][j] = min (dis[i][j], dis[i][k] + dis[k][j]);
                }
            }
        }
    }
}