

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Selection {
	private:
	std::vector<T> vec;

	public:

	Selection (std::vector<T> vec) : vec (vec) {}

	void sort () {
		for (int i = 0; i < vec.size(); i++) {
			int min = i;
			for (int j = i + 1; j < vec.size(); j++) {
				if (vec[j] < vec[min]) {
					min = j;
				}
			}

			std::swap (vec[min], vec[i]);
		}
	}

	void print () {
		for (auto i : vec) {
			std::cout << i << ' ';
		}
		std::cout << std::endl;
	}
};