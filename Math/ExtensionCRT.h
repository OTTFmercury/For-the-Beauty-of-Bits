

#include <vector>
#include "ExtensionGCD.h"

using std::pair;
using std::vector;

template <typename T>
T ExtenxionCRT (vector<pair<T, T>> ques) {
	auto [m, a] = ques[0];
	for (int i = 1; i < ques.size(); i++) {
		auto [n, b] = ques[i];
		// mp + a = nq + b
		// mp - nq = b - a
		auto [gcd, p, q] = exgcd (m, n);
		auto minus = ((b - a) % n + n) % n;

		p = mul (p, (minus / gcd), n);
		p = (p % n + n) % n;

		a = m * p + a;
		m = m * (n / gcd);
		a = (a % m + m) % m;
	}
	return a;
}