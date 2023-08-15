

#include <cmath>
#include <vector>

using std::vector;

template<typename NumT, typename ResT, int MaxLog, ResT (*Fun1) (NumT one), ResT (*Fun2) (ResT one, ResT two)>
class SparseTable {
	private:
	vector<vector<int>> res;

	public:

	SparseTable () = default;
	SparseTable (vector<NumT> nums);
	ResT cal (int l, int r);
};

template<typename NumT, typename ResT, int MaxLog, ResT (*Fun1) (NumT one), ResT (*Fun2) (ResT one, ResT two)>
SparseTable<NumT, ResT, MaxLog, Fun1, Fun2>::SparseTable (vector<NumT> nums) {
	res.resize(MaxLog);

	for (int i = 0; i < nums.size(); i++) {
		res[0].push_back(Fun1 (nums[i]));
	}

	for (int i = 1; i < res.size(); i++) {
		for (int j = 0; j + (1 << (i - 1)) < nums.size(); j++) {
			res[i].push_back(Fun2 (res[i - 1][j], res[i - 1][j + (1 << (i - 1))]));
		}
	}
}

template<typename NumT, typename ResT, int MaxLog, ResT (*Fun1) (NumT one), ResT (*Fun2) (ResT one, ResT two)>
ResT SparseTable<NumT, ResT, MaxLog, Fun1, Fun2>::cal (int l, int r) {
	int num = log2 (r - l + 1.0);
	return Fun2 (res[num][l], res[num][r - (1 << num) + 1]);
}