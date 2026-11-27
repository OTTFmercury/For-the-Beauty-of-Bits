

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