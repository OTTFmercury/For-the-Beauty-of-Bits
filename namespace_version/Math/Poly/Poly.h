

#include <algorithm>
#include <cstring>

const int N = 1145140;
const long long Mod = 998244353;

template <typename T>
T my_pow (T a, T n) {
	T res = 1;
	while (n) {
		if (n & 1) {
			res = res * a % Mod;
		}
		a = a * a % Mod;
		n >>= 1;
	}
	return res % Mod;
}

namespace NTT {
	/*
	require:
		constant : N, Mod
		funcction : my_pow
		head file : algorithm
	*/
	
	const long long rt = 3;
	const long long rti = 332748118;
	long long cc = 0;
	long long limit = 1;
	long long change[N];
	
	void init_limit (const int & n, const int & m) {
		while (limit <= n + m) {
			limit <<= 1;
			cc++;
		}
	}
	
	void init_change () {
		for (int i = 0; i < limit; i++) {
			change[i] = (change[i >> 1] >> 1) | ((i & 1) << (cc - 1));
		}
	}
	
	void init_all (const int & n, const int & m) {
		init_limit (n, m);
		init_change ();
	}
	
	void ntt (long long nums[N], int flag) {
		for (int i = 0; i < limit; i++) {
			if (i < change[i]) {
				std::swap (nums[i], nums[change[i]]);
			}
		}
		
		for (long long mid = 1; mid < limit; mid <<= 1) {
			long long W = my_pow (((flag == 1) ? rt : rti), (Mod - 1) / (mid << 1));
			
			for (long long r = mid << 1, j = 0; j < limit; j += r) {
				long long w = 1;
				
				for (long long l = 0; l < mid; l++, w = w * W % Mod) {
					long long x = nums[j + l];
					long long y = w * nums[j + mid + l] % Mod;
	
					nums[j + l] = (x + y) % Mod;
					nums[j + mid + l] = (x - y + Mod) % Mod;
				}
			}
		}
	}
}

namespace Poly_Mult {
	/*
	require:
		constant : N, Mod
		function : my_pow
		namespace : NTT
	*/
	
	void init (int n, int m) {
		NTT::init_all (n, m);
	}
	
	void solve (long long a[N], int n, long long b[N], int m, long long res[N], bool flag) {
		NTT::ntt (a, 1);
		if (a != b) {
			NTT::ntt (b, 1);
		}
		
		for (int i = 0; i < NTT::limit; i++) {
			res[i] = a[i];
			res[i] *= b[i];
			res[i] %= Mod;
		}
		
		NTT::ntt (res, -1);
	
		long long inv = my_pow (NTT::limit, Mod - 2);
	
		for (int i = 0; i < n + m + 1; i++) {
			res[i] = res[i] * inv % Mod;
		}
	}
	
	void init_solve (long long a[N], int n, long long b[N], int m, long long res[N], bool flag = false) {
		init (n, m);
		solve (a, n, b, m, res, flag);
	}
}

namespace Poly_Mult_Inv {
	/*
	require:
		constant : N, Mod
		function : my_pow
		namespace : NTT, Poly_Mult
	*/
	
	long long at[N];
	long long b[2][N];
	
	void solve (long long a[N], int n, long long res[N]) {
		int t = 0;
		int base_limit = 1;
		int single_len = 2;
		
		b[0][0] = my_pow (a[0], Mod - 2);
		
		while (base_limit < (n - 1) * 2) {
			t ^= 1;
			memset (b[t], 0, sizeof (b[t]));
			
			for (int i = 0; i <= base_limit; i++) {
				b[t][i] = (b[t ^ 1][i] << 1) % Mod;
			}
			
			Poly_Mult::init_solve (b[t ^ 1], single_len, b[t ^ 1], single_len, b[t ^ 1]);
			
			for (int i = 0; i <= single_len; i++) {
				at[i] = a[i];
			}
			Poly_Mult::init_solve (b[t ^ 1], single_len, at, single_len, b[t ^ 1], true);
			
			for (int i = 0; i <= base_limit; i++) {
				b[t][i] = (b[t][i] + Mod - b[t ^ 1][i]);
				if (b[t][i] >= Mod) {
					b[t][i] -= Mod;
				}
			}
			
			base_limit <<= 1;
			single_len <<= 1;
		}
		
		for (int i = 0; i < n; i++) {
			res[i] = b[t][i];
		}
	}
}

namespace FWT {
	/*
	require:
		constant : N, Mod
	*/

	long long limit;
	
	void init (const int & n) {
		limit = n;
	}
	
	void fwt (long long nums[N], long long arr[2][2]) {
		for (long long mid = 1; mid < limit; mid <<= 1) {
			for (long long r = mid << 1, j = 0; j < limit; j += r) {
				for (long long l = 0; l < mid; l++) {
					auto left = ((nums[j + l] * arr[0][0] + nums[j + mid + l] * arr[0][1]) % Mod + Mod) % Mod;
					auto right = ((nums[j + l] * arr[1][0] + nums[j + mid + l] * arr[1][1]) % Mod + Mod) % Mod;
					nums[j + l] = left;
					nums[j + mid + l] = right;
				}
			}
		}
	}
}

namespace Poly_Bit_Oper_Mult {
	/*
	require:
		constant : N, Mod
		namespace : FWT
	*/

	long long A[N];
	long long B[N];
	enum bit_operation : int {bit_or = 0, bit_and = 1, bit_xor = 2};
	const long long Half = (Mod + 1) / 2;
	long long arr[3][2][2][2] = {
		{{{1, 0}, {1, 1}}, {{1, 0}, {-1, 1}}},
		{{{1, 1}, {0, 1}}, {{1, -1}, {0, 1}}},
		{{{1, 1}, {1, -1}}, {{Half, Half}, {Half, -Half}}}
	};
	
	void solve (long long a[N], long long b[N], long long res[N], const int & len, long long one[2][2], long long two[2][2]) {
		for (int i = 0; i < len; i++) {
			A[i] = a[i];
			B[i] = b[i];
		}
		
		FWT::init (len);
		FWT::fwt (A, one);
		FWT::fwt (B, one);
		for (int i = 0; i < len; i++) {
			res[i] = (A[i] * B[i] % Mod + Mod) % Mod;
		}
		FWT::fwt (res, two);
	}
	
	void solve (long long a[N], long long b[N], long long res[N], const int & len, bit_operation op) {
		solve (a, b, res, len, arr[op][0], arr[op][1]);
	}
}