template <typename T = int>
class Stack {
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

	Stack () = default;
	~Stack () {
		delete [] ptr;
	}

	bool empty () {
		return !n;
	}

	void push (T elem) {
		if (n == capacity) {
			resize (capacity * 2);
		}

		ptr[n++] = elem;
	}

	void pop () {
		if (empty ()) {
			throw "Nga? Pop when this stack is empty?";
		}

		if ((n == capacity / 4) && (capacity > 16)) {
			resize (capacity / 2);
		}

		n--;
	}

	T top () {
		if (empty ()) {
			throw "Nga? Get top when this stack is empty?";
		}

		return ptr[n - 1];
	}
};