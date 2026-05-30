

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Merge {
	private:
	std::vector<T> vec;

	void merge (int l, int m, int r) {
		std::vector<T> t = vec;

		int li = l;
		int ri = m + 1;
		for (int i = l; i <= r; i++) {
			if (li > m) {
				vec[i] = t[ri++];
			}
			else if (ri > r) {
				vec[i] = t[li++];
			}
			else if (t[li] < t[ri]) {
				vec[i] = t[li++];
			}
			else {
				vec[i] = t[ri++];
			}
		}
	}

	void sort (int l, int r) {
		if (l >= r) {
			return;
		}

		int m = (l + r) / 2;

		sort (l, m);
		sort (m + 1, r);
		merge (l, m, r);
	}

	public:

	Merge (std::vector<T> vec) : vec (vec) {}

	void sort () {
		sort (0, vec.size() - 1);
	}

	void print () {
		for (auto i : vec) {
			std::cout << i << ' ';
		}
		std::cout << std::endl;
	}
};