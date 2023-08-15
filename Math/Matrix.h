

#include <vector>

using std::vector;

const int mod = 1e9 + 7;

template <typename T>
class Matrix {
	private:
	int n;
	int m;
	vector<vector<T>> matrix {};

	public:

	Matrix (int n, int m) : n (n), m (m) {
		matrix.resize(n + 10);
		for (auto &arr : matrix) {
			arr.resize(m + 10);
		}
	}

	const Matrix operator* (const Matrix other) const {
		Matrix res (n, other.m);

		if (m == other.n) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= other.m; j++) {
					for (int k = 1; k <= m; k++) {
						res[i][j] += matrix[i][k] * other.matrix[k][j];
						res[i][j] %= mod;
					}
				}
			}
		}
		return res;
	}

	vector<T>& operator[] (int num) {
		return matrix[num];
	}

};