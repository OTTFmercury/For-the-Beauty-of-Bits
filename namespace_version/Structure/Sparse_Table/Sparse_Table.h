

#include <algorithm>

const int N = 1000005;
const int Maxn = 1000005;

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

const int Log2N = 20;

namespace Sparse_Table_Max {
    /*
    require:
        constant: N
        function: max
        namespace: Log2
    
    need to init:
        Log2::init ()
    */
   
    using std::max;

    void init (int nums[N], int st[Log2N][N], int a) {
        for (int i = 1; i <= a; i++) {
            st[0][i] = nums[i];
        }

        for (int k = 1; k < Log2N; k++) {
            for (int i = 1; i + (1 << (k - 1)) <= a; i++) {
                st[k][i] = max (st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    int query (int st[Log2N][N], int left, int len) {
        int k = Log2::log2[len];
        return max (st[k][left], st[k][left + len - (1 << k)]);
    }
}

namespace Sparse_Table_Min {
    /*
    require:
        constant: N
        function: min
        namespace: Log2
    
    need to init:
        Log2::init ()
    */
   
    using std::min;

    void init (int nums[N], int st[Log2N][N], int a) {
        for (int i = 1; i <= a; i++) {
            st[0][i] = nums[i];
        }

        for (int k = 1; k < Log2N; k++) {
            for (int i = 1; i + (1 << (k - 1)) <= a; i++) {
                st[k][i] = min (st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    int query (int st[Log2N][N], int left, int len) {
        int k = Log2::log2[len];
        return min (st[k][left], st[k][left + len - (1 << k)]);
    }
}