
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

namespace Chinese_Remainder_Theorem {
    /*
    require:
        constant: N
        namespace: Extended_Greatest_Common_Divisor
    */

    __int128 crt (int n, __int128 divisor[N], __int128 remainder[N]) {
        /*
        function:
            find the smallest non-negative integer solution for the following system:
                x === remainder_1 (mod divisor_1)
                x === remainder_2 (mod divisor_2)
                ...
                x === remainder_n (mod divisor_n)
            where the divisors are pairwise coprime
        */

        /*
        step1:
            from the additivity of remainders, if we can find solutions to the following n equations, we can find the solution to the original equation:
                equation_1:
                    x_1 === remainder_1 (mod divisor_1)
                    x_1 === 0 (mod divisor_2)
                    ...
                    x_1 === 0 (mod divisor_n)
                equation_2:
                    x_2 === 0 (mod divisor_1)
                    x_2 === remainder_2 (mod divisor_2)
                    ...
                    x_2 === 0 (mod divisor_n)
                ...
                equation_n:
                    x_n === 0 (mod divisor_1)
                    x_n === 0 (mod divisor_2)
                    ...
                    x_n === remainder_n (mod divisor_n)
            thus, x = x_1 + x_2 + .. + x_n
        */

        /*
        step2:
            from the multiplicability of remainders, if we can find solutions to the following equation, we can find the solution to eauqtion_i:
                equation_i_':
                    x_i_' === 0 (mod divisor_1)
                    x_i_' === 0 (mod divisor_2)
                    ...
                    x_i_' === 1 (mod divisor_i)
                    ...
                    x_i_' === 0 (mod divisor_n)
            thus, x_i = x_i_'
        */

        /*
        step3:
            every divisor divides x_i except divisor_i, and they are pairwise coprime
            so let big_mult = divisor_1 * divisor_1 * ... divisor_i * .. divisor_n, now_mult = big_mult / divisor_i
            now_mult divides x_i_'
        */

        /*
        step4:
            let x_i_' = now_mult * k
            thus, now_mult * k === 1 (mod divisor_i)
            thus, now_mult * k + divisor_i * k_' == 1
            which can be solved with exgcd
        */

        __int128 big_mult = 1;
        for (int i = 1; i <= n; i++) {
            big_mult = big_mult * divisor[i];
        }

        __int128 x = 0;
        for (int i = 1; i <= n; i++) {
            __int128 now_mult = big_mult / divisor[i];
            auto [_, k, k_] = Extended_Greatest_Common_Divisor::exgcd (now_mult, divisor[i]);

            __int128 x_i = now_mult * k % big_mult;
            x_i = x_i * remainder[i] % big_mult;

            x += x_i;
            x %= big_mult;
        }

        return (x % big_mult + big_mult) % big_mult;
    }
}