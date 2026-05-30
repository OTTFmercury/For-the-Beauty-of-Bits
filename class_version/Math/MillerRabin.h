

#include <initializer_list>
#include "QuickMul.h"
#include "QuickPower.h"

bool MillerRabin (long long n) {
	if (n < 3 || n % 2 == 0) {
		return n == 2;
	}
	long long u = n - 1;
	long long t = 0;
	while (u % 2 == 0) {
		t++;
		u /= 2;
	}
	for (long long a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
		long long v = pow (a, u, n);
		if (v == 0 || v == 1 || v == n - 1) {
			continue;
		}
		for (int i = 1; i <= t; i++) {
			v = mul (v, v, n);
			if (v == n - 1 && i != t) {
				v = 1;
				break;
			}
			if (v == 1) {
				return false;
			}
		}
		if (v != 1) {
			return false;
		}
	}
	return true;
}