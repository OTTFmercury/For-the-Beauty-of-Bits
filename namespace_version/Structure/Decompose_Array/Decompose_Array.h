

#include <cmath>

const int N = 200010;

namespace Decompose_Array {
    /*
    require:
        constant: N
        function: sqrt
        headfile: cmath
    */

    using std::sqrt;

    void solve (int n, int & block_len, int & block_num, int belong_to[N], int block_left[N], int block_right[N]) {
        block_len = sqrt (n);
        if (block_len == 1) {
            block_len = 2;
        }

        block_num = 0;

        for (int i = 1; i <= n; i++) {
            if (i % block_len == 1) {
                block_num++;
                belong_to[i] = block_num;
                block_left[block_num] = i;
            }
            else {
                belong_to[i] = belong_to[i - 1];
            }

            if ((i % block_len == 0) || (i == n)) {
                block_right[block_num] = i;
            }
        }
    }
}