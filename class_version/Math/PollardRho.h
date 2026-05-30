

#include <algorithm>
#include <cmath>
#include <random>
#include "MillerRabin.h"

std::mt19937 engine;

inline long long gcd (long long x, long long y) {
	long long z;
	while (y) {
		z = x;
		x = y;
		y = z % y;
	}
	return x;
}

long long PollardRho (long long num) {
	if (num == 4) {
		return 2;
	}
	std::uniform_int_distribution<long long> rand(3, num - 1);
	long long x, y, z, c, g;
	int i, j;
	while (true) {
		x = rand (engine);
		y = x;
		z = 1;
		c = rand (engine);
		for (i = 1, j = 1; true; i++) {
			x = (mul (x, x, num) + c) % num;
			z = mul (z, abs (x - y), num);
			if (x == y || !z) {
				break;
			}
			if (i % 127 == 0 || i == j) {
				g = gcd (z, num);
				if (g > 1) {
					return g;
				}
				if (i == j) {
					y = x;
					j <<= 1;
				}
			}
		}
	}
}

void dfs (long long num, long long &res) {
	if (num == 1) {
		return;
	}
	if (num <= res) {
		return;
	}
	if (MillerRabin (num)) {
		res = std::max (res, num);
		return;
	}
	long long p = PollardRho (num);
	while (num % p == 0) {
		num /= p;
	}
	dfs (num, res);
	dfs (p, res);
}

long long getMaxFactor (long long num) {
	long long res = 0;
	dfs (num, res);
	return res;
}