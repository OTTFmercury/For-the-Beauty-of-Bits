

#include <algorithm>
#include <cmath>

using namespace std;

const int N = 15;
const long double eps = 1e-6;

namespace Gauss_Eli {
    /*
	require:
		constant : N
		funcction : abs swap
		head file : algorithm cmath
	*/

	void solve (long double arr[N][N], long double res[N], int n) {
		int main_line = 1;
		for (int i = 1; i <= n; i++) {
			int maxn_line = main_line;
			for (int j = main_line + 1; j <= n; j++) {
				if (abs (arr[maxn_line][i]) < abs (arr[j][i])) {
					maxn_line = j;
				}
			}
			if (abs (arr[maxn_line][i]) < eps) {
				continue;
			}

			if (main_line != maxn_line) {
				swap (arr[main_line], arr[maxn_line]);
			}

			for (int j = 1; j <= n; j++) {
				if (j == main_line) {
					continue;
				}
				double t = arr[j][i] / arr[main_line][i];
				for (int k = main_line; k <= n + 1; k++) {
					arr[j][k] -= arr[main_line][k] * t;
				}
			}
			main_line++;
		}

		if (main_line <= n) {
			while (main_line <= n) {
				if (abs (arr[main_line++][n + 1]) > eps) {
					res[0] = -1;
					return;
				}
			}
			res[0] = 1;
			return;
		}

		for (int i = 1; i <= n; i++) {
			res[i] = arr[i][n + 1] / arr[i][i];
		}
	}
}