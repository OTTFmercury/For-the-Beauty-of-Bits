

#include "QuickPower.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

using std::vector;

template <typename T, const T Mod>
class Matrix {
	private:
	int n;
	int m;
	vector<vector<T>> matrix {};

	public:

	Matrix (int n, int m) : n (n), m (m){
		matrix.resize(n + 10);
		for (auto &arr : matrix) {
			arr.resize(m + 10);
		}
	}

	const Matrix operator* (const Matrix other) const {
		Matrix res (n, other.m);

		assert (m == other.n);

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= other.m; j++) {
				for (int k = 1; k <= m; k++) {
					res[i][j] += matrix[i][k] * other.matrix[k][j];
					if (haveMod) {
						res[i][j] %= Mod;
					}
				}
			}
		}
		return res;
	}

	vector<T>& operator[] (int num) {
		return matrix[num];
	}

	void display () {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cout << matrix[i][j] << ' ';
			}
			cout << endl;
		}
	}

	vector<T> GaussianElimination (T eps) {
		vector<T> res;
		res.resize(n + 1);

		assert (n + 1 == m);

		int line = 1;
		for (int i = 1; i <= n; i++) {
			int r = line;
			for (int j = line + 1; j <= n; j++) {
				if (abs (matrix[r][i]) < abs (matrix[j][i])) {
					r = j;
				}
			}
			if (abs (matrix[r][i]) < eps) {
				continue;
			}

			if (line != r) {
				swap (matrix[line], matrix[r]);
			}

			for (int j = 1; j <= n; j++) {
				if (j == line) {
					continue;
				}
				T t = matrix[j][i] / matrix[line][i];
				for (int k = line; k <= n + 1; k++) {
					matrix[j][k] -= matrix[line][k] * t;
				}
			}
			line++;
		}

		if (line <= n) {
			while (line <= n) {
				if (abs (matrix[line++][n + 1]) > eps) {
					res[0] = -1;
					return res;
				}
			}
			res[0] = 1;
			return res;
		}

		for (int i = 1; i <= n; i++) {
			res[i] = matrix[i][n + 1] / matrix[i][i];
		}
		return res;
	}

	Matrix<T, Mod> operator~ () {
		assert (n == m);

		Matrix<T, Mod> extra = *this;
		Matrix<T, Mod> res = *this;
		extra.m = n * 2;
		for (int i = 1; i <= n; i++) {
			extra[i].resize(n * 2 + 10);
			extra[i][n + i] = 1;
		}

		for (int i = 1; i <= n; i++) {
			int r = i;
			for (int j = i + 1; j <= n; j++) {
				if (extra[j][i] > extra[r][i]) {
					r = j;
				}
			}
			if (r != i) {
				swap (extra[r], extra[i]);
			}

			if (!extra[i][i]) {
				res[0][0] = -1;
				return res;
			}

			T num = pow<T> (extra[i][i], Mod - 2, Mod);

			for (int j = 1; j <= n; j++) {
				if (i == j) {
					continue;
				}
				T temp = extra[j][i] * num % Mod;
				for (int k = i; k <= 2 * n; k++) {
					extra[j][k] = ((extra[j][k] - temp * extra[i][k]) % Mod + Mod) % Mod;
				}
			}

			for (int j = 1; j <= 2 * n; j++) {
				extra[i][j] = (extra[i][j] * num % Mod);
			}
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				res[i][j] = extra[i][j + n];
			}
		}

		return res;
	}
};