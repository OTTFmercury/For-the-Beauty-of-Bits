long long mul (long long a, long long b, long long mod) {
	long long c = (long double) a / mod * b;
	long long res = (unsigned long long) a * b - (unsigned long long) c * mod;
	return (res + mod) % mod;
}