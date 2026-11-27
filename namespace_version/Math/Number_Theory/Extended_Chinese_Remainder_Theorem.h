
#include <tuple>

using std::make_tuple;
using std::tuple;

namespace Extended_Greatest_Common_Divisor {
    /*
    require:
        class: tuple
        function: make_tuple
        headfile: tuple
    */

    template <typename T>
    tuple<T, T, T> exgcd (T a, T b) {
        if (b == 0) {
            return make_tuple (a, 1, 0);
        }

        auto [res, lastX, lastY] = exgcd (b, a % b);
        
        return make_tuple (res, lastY, lastX - a / b * lastY);
    }
}

const int N = 14;

namespace Extended_Chinese_Remainder_Theorem {
    /*
    require:
        constant: N
        namespace: Extended_Greatest_Common_Divisor
    */

    template <typename T>
    T excrt (int n, T divisor[N], T remainder[N]) {
        auto m = divisor[0];
        auto a = remainder[0];
        for (int i = 1; i <= n; i++) {
            auto n = divisor[i];
            auto b = remainder[i];
            // mp + a = nq + b
            // mp - nq = b - a
            auto [gcd, p, q] = Extended_Greatest_Common_Divisor::exgcd (m, n);
            auto minus = ((b - a) % n + n) % n;
            p = (p * (minus / gcd) % n + n) % n;

            a = m * p + a;
            m = m * (n / gcd);
            a = (a % m + m) % m;
        }
        return a;
    }
}