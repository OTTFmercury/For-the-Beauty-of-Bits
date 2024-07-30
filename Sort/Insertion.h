

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Insertion {
	private:
	std::vector<T> vec;

	public:

	Insertion (std::vector<T> vec) : vec (vec) {}

	void sort () {
		for (int i = 1; i < vec.size(); i++) {
			for (int j = i; j > 0 && vec[j] < vec[j - 1]; j--) {
				std::swap (vec[j], vec[j - 1]);
			}
		}
	}
};