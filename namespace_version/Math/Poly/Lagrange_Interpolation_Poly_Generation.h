

const int N = 114;
const long long Mod = 1e9 + 7;

namespace Quick_Pow {
    template <typename T>
    T quick_pow (T a, T n) {
        T res = 1;
        while (n) {
            if (n & 1) {
                res = res * a % Mod;
            }
            a = a * a % Mod;
            n >>= 1;
        }
        return res;
    }

    template <typename T>
    T inv (T a) {
        return quick_pow (a, Mod - 2);
    }
}

using namespace Quick_Pow;

namespace Lagrange_Interpolation_Poly_Generation {
    /*
    require:
        constant: Mod N
        namespace: Quick_Pow
    */

    long long dp[N][N];

    void solve (long long x[N], long long y[N], int n, long long coefficient[N]) {
        long long mult;
        long long t;

        for (int u = 1; u <= n; u++) {
            mult = dp[0][0] = 1;

            for (int i = 1; i <= n; i++) {
                if (u == i) {
                    for (int j = 0; j < n; j++) {
                        dp[i][j] = dp[i - 1][j];
                    }
                    continue;
                }

                t = ((-x[i]) % Mod + Mod) % Mod;
                
                dp[i][0] = dp[i - 1][0] * t % Mod;
                for (int j = 1; j < n; j++) {
                    dp[i][j] = (dp[i - 1][j] * t % Mod + dp[i - 1][j - 1]) % Mod;
                }
                
                mult = mult * quick_pow (((x[u] - x[i]) % Mod + Mod) % Mod, Mod - 2) % Mod;
            }

            for (int i = 0; i < n; i++) {
                coefficient[i] = (coefficient[i] + dp[n][i] * y[u] % Mod * mult % Mod) % Mod;
            }
        }
    }
}