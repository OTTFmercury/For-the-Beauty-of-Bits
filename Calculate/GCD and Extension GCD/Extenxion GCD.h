

#include <tuple>

using namespace std;

template <typename T>
tuple<T, T, T> exgcd (T a, T b) {
	if (b == 0) {
		return make_tuple (a, 1, 0);
	}

	auto [res, lastX, lastY] = exgcd (b, a % b);
	
	return make_tuple (res, lastY, lastX - a / b * lastY);
}