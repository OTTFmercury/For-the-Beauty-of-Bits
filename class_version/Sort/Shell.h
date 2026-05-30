

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Shell {
	private:
	std::vector<T> vec;

	public:

	Shell (std::vector<T> vec) : vec (vec) {}

	void sort () {
		int h = 1;
		while (h < vec.size() / 3) {
			h = h * 3 + 1;
		}

		while (h >= 1) {
			for (int i = 1; i < vec.size(); i++) {
				for (int j = i; j > 0 && vec[j] < vec[j - h]; j -= h) {
					std::swap (vec[j], vec[j - h]);
				}
			}

			h /= 3;
		}

	}

	void print () {
		for (auto i : vec) {
			std::cout << i << ' ';
		}
		std::cout << std::endl;
	}
};