

#include <cstring>

const int N = 15;

struct Matrix {
    /*
    option:
        define: USE_CONSTANT_MOD, then, constant: Mod
    require:
        constant: N
    */

    int arr[N][N];
    int m;
    int n;

    Matrix () : m (0), n (0) {
        memset (arr, 0, sizeof (arr));
    };
    Matrix (int m, int n) : m (m), n (n) {
        memset (arr, 0, sizeof (arr));
    }

    int* operator[] (int num) {
        return arr[num];
    }

    Matrix operator* (Matrix other) {
        if (n != other.m) {
            throw "A.n should = B.m";
        }

        int p = other.n;
        Matrix res (m, p);

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= p; j++) {
                res[i][j] = 0;
                for (int k = 1; k <= n; k++) {
                    #ifdef USE_CONSTANT_MOD
                    res[i][j] = (res[i][j] + (long long) (arr[i][k]) * (long long) (other[k][j]) % Mod) % Mod;
                    #else
                    res[i][j] = res[i][j] + arr[i][k] * other[k][j];
                    #endif
                }
            }
        }

        return res;
    }

    void operator*= (Matrix other) {
        (*this) = (*this) * other;
    }
};