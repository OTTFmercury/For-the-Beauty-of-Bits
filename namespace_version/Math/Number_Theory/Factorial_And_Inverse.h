

namespace Quick_Pow {
    /*
    option:
        define: USE_CONSTANT_MOD, then, constant: Mod
    */

    template <typename Element, typename Exponent>
    Element quick_pow (Element a, Exponent n, Element identity_element) {
        Element res = identity_element;
        while (n) {
            if (n & 1) {
                res *= a;
            }
            a *= a;
            n >>= 1;
        }
        return res;
    }

    template <typename Element, typename Exponent>
    Element quick_pow_mod (Element a, Exponent n, Element identity_element, Element mod) {
        Element res = identity_element;
        while (n) {
            if (n & 1) {
                res = res * a % mod;
            }
            a = a * a % mod;
            n >>= 1;
        }
        return res;
    }

    #ifdef USE_CONSTANT_MOD
    template <typename Element, typename Exponent>
    Element quick_pow_constant_mod (Element a, Exponent n, Element identity_element) {
        Element res = identity_element;
        while (n) {
            if (n & 1) {
                res = res * a % Mod;
            }
            a = a * a % Mod;
            n >>= 1;
        }
        return res;
    }
    #endif

    template <typename Element>
    Element inv_mod (Element a, Element mod) {
        return quick_pow_mod (a, mod - 2, (Element) (1), mod);
    }

    #ifdef USE_CONSTANT_MOD
    template <typename Element>
    Element inv_constant_mod (Element a) {
        return quick_pow_constant_mod (a, Mod - 2, (Element) (1));
    }
    #endif
}

const int N = 1e5 + 10;

namespace Factorial_And_Inverse {
    /*
    require:
        constant: N
        namespace: Quick_Pow
    */

    void solve (long long fact[N], long long inv[N], long long n, long long mod) {
        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i % mod;
        }
        inv[n] = Quick_Pow::inv_mod (fact[n], mod);
        for (int i = n - 1; i >= 0; i--) {
            inv[i] = inv[i + 1] * (i + 1) % mod;
        }
    }
}