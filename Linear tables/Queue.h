template <typename T = int>
class Queue {
	private:
	T* ptr = new T[16];
	int capacity = 16;
	int first = 0;
	int last = 0;

	void resize (int size) {
		T* nPtr = new T[size];
		for (int i = first; i < last; i++) {
			nPtr[i] = ptr[i];
		}

		delete [] ptr;
		ptr = nPtr;

		capacity = size;
	}

	public:

	Queue () = default;
	~Queue () {
		delete [] ptr;
	}

	bool empty () {
		return !(last - first);
	}

	void enqueue (T elem) {
		if (last == capacity) {
			resize (capacity * 2);

			last -= first;
			first = 0;
		}

		ptr[last++] = elem;
	}

	void dequeue () {
		if (empty ()) {
			throw "Nga? Dequeue when this queue is empty?";
		}

		if ((last - first) == capacity / 4) {
			resize (capacity / 2);

			last -= first;
			first = 0;
		}

		first++;
	}

	T front () {
		if (empty ()) {
			throw "Nga? Get front when this queue is empty?";
		}

		return ptr[first];
	}

	T back () {
		if (empty ()) {
			throw "Nga? Get back when this queue is empty?";
		}

		return ptr[last - 1];
	}
};