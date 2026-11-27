

#include <algorithm>

const int Maxn = 1145;

namespace Log2 {
    /*
    require:
        constant: Maxn
    */
    int log2[Maxn];
    
    void init () {
        for (int i = 2; i < Maxn; i++) {
            log2[i] = log2[i / 2] + 1;
        }
    }
}

const int N = 1145;
const int Log2N = 15;

namespace Sparse_Table_Max_2D {
    /*
    require:
        constant: Maxn, N
        function: max
        headfile: algorithm
        namespace: Log2
    need to init:
        Log2::init ()
    */

    using std::max;

    void init (int nums[N][N], int st[Log2N][N][N], int a, int b) {
        for (int i = 1; i <= a; i++) {
            for (int j = 1; j <= b; j++) {
                st[0][i][j] = nums[i][j];
            }
        }

        for (int k = 1; k < Log2N; k++) {
            for (int i = 1; i + (1 << (k - 1)) <= a; i++) {
                for (int j = 1; j + (1 << (k - 1)) <= b; j++) {
                    st[k][i][j] = max ({st[k - 1][i][j], st[k - 1][i + (1 << (k - 1))][j], st[k - 1][i][j + (1 << (k - 1))], st[k - 1][i + (1 << (k - 1))][j + (1 << (k - 1))]});
                }
            }
        }
    }

    int query (int st[Log2N][N][N], int up, int left, int len) {
        int log2 = Log2::log2[len];
        return max ({st[log2][up][left], st[log2][up + len - (1 << log2)][left], st[log2][up][left + len - (1 << log2)], st[log2][up + len - (1 << log2)][left + len - (1 << log2)]});
    }
}

namespace Sparse_Table_Min_2D {
    /*
    require:
        constant: Maxn, N
        function: min
        headfile: algorithm
        namespace: Log2
    
    need to init:
        Log2::init ()
    */
   
    using std::min;

    void init (int nums[N][N], int st[Log2N][N][N], int a, int b) {
        for (int i = 1; i <= a; i++) {
            for (int j = 1; j <= b; j++) {
                st[0][i][j] = nums[i][j];
            }
        }

        for (int k = 1; k < Log2N; k++) {
            for (int i = 1; i + (1 << (k - 1)) <= a; i++) {
                for (int j = 1; j + (1 << (k - 1)) <= b; j++) {
                    st[k][i][j] = min ({st[k - 1][i][j], st[k - 1][i + (1 << (k - 1))][j], st[k - 1][i][j + (1 << (k - 1))], st[k - 1][i + (1 << (k - 1))][j + (1 << (k - 1))]});
                }
            }
        }
    }

    int query (int st[Log2N][N][N], int up, int left, int len) {
        int k = Log2::log2[len];
        return min ({st[k][up][left], st[k][up + len - (1 << k)][left], st[k][up][left + len - (1 << k)], st[k][up + len - (1 << k)][left + len - (1 << k)]});
    }
}