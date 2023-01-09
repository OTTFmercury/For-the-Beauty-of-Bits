

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Quick {
	private:
	std::vector<T> vec;

	int partition (int l, int r) {
		int val = vec[l];
		int li = l;
		int ri = r + 1;

		while (true) {
			while (vec[++li] < val) {
				if (li == r) {
					break;
				}
			}
			while (vec[--ri] > val) {
				if (ri == l) {
					break;
				}
			}

			if (li >= ri) {
				break;
			}
			std::swap (vec[li], vec[ri]);
		}

		std::swap (vec[l], vec[ri]);

		return ri;
	}

	void sort (int l, int r) {
		if (l >= r) {
			return;
		}

		int m = partition (l, r);
		sort (l, m - 1);
		sort (m + 1, r);
	}

	public:

	Quick (std::vector<T> vec) : vec (vec) {}

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