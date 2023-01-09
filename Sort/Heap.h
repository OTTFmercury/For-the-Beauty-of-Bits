

#include <algorithm>

template <typename T = int>
class Heap {
	private:
	T* ptr = new T[16];
	int capacity = 16;
	int n = 0;

	void resize (int size) {
		T* nPtr = new T[size];
		for (int i = 0; i < size && i < capacity; i++) {
			nPtr[i] = ptr[i];
		}

		delete [] ptr;
		ptr = nPtr;

		capacity = size;
	}

	public:

	Heap () = default;
	~Heap () {
		delete [] ptr;
	}

	bool empty () {
		return !n;
	}

	void swim (int num) {
		while (num > 1 && ptr[num / 2] < ptr[num]) {
			std::swap (ptr[num], ptr[num / 2]);
			num /= 2;
		}
	}

	void sink (int num) {
		while (true) {
			if ((num * 2 <= n) && (ptr[num * 2] > ptr[num])) {
				std::swap (ptr[num], ptr[num * 2]);
			}
			else if ((num * 2 + 1 <= n) && (ptr[num * 2 + 1] > ptr[num])) {
				std::swap (ptr[num], ptr[num * 2 + 1]);
			}
			else {
				break;
			}
		}
	}

	void push (T elem) {
		if (n + 1 == capacity) {
			resize (capacity * 2);
		}

		ptr[++n] = elem;
		swim (n);
	}

	T top () {
		return ptr[1];
	}

	T pop () {
		T res = ptr[1];

		std::swap (ptr[1], ptr[n--]);
		sink (1);

		return res;
	}
};