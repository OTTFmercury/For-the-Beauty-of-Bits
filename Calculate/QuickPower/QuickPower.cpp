template <typename T>
int pow (T a, T n, T mod) {
	T res = 1;
	while (n) {
		if (n & 1) {
			res = (res % mod) * (a % mod) % mod;
		}
		a = (a % mod) * (a % mod) % mod;
		n >>= 1;
	}
	return res % mod;
}