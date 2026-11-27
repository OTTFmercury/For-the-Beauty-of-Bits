

const int N = 2010;
const long long Mod = 998244353;

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

namespace Lagrange_Interpolation {
    /*
    require:
        constant: Mod N
        function: quick_pow
    */
    long long solve (long long x[N], long long y[N], int n, long long k) {
        long long res = 0;

        for (int i = 1; i <= n; i++) {
            long long son = y[i] % Mod;
            long long mom = 1;
            for (int j = 1; j <= n; j++) {
                if (i == j) {
                    continue;
                }

                son = (son * (k - x[j])) % Mod;
                mom = (mom * (x[i] - x[j])) % Mod;
            }

            long long ans = son * quick_pow (mom, Mod - 2) % Mod;
            res = (res + ans) % Mod;
        }

        res = (res % Mod + Mod) % Mod;
        return res;
    }
}