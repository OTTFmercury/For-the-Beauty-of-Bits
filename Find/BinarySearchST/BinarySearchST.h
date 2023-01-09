

#include <algorithm>

namespace ForBinarySearchST {
	template <typename Key, typename Val>
	struct Pair {
		Key key;
		Val val;

		Pair () = default;
		Pair (Key key, Val val) : key (key), val (val) {}
	};
};

using namespace ForBinarySearchST;

template <typename Key, typename Val>
class BinarySearchST {
	private:

	Pair<Key, Val>* ptr = new Pair<Key, Val>[16];
	int capacity = 16;
	int n = 0;

	void resize (int size) {
		Pair<Key, Val>* nPtr = new Pair<Key, Val>[size];
		for (int i = 0; i < size && i < capacity; i++) {
			nPtr[i] = ptr[i];
		}

		delete [] ptr;
		ptr = nPtr;

		capacity = size;
	}

	int rank (Key key) {
		int l = 0;
		int r = n - 1;

		while (l <= r) {
			int m = (l + r) / 2;

			if (ptr[m].key < key) {
				l = m + 1;
			}
			else if (ptr[m].key > key) {
				r = m - 1;
			}
			else {
				return m;
			}
		}

		return l;
	}

	public:

	BinarySearchST () = default;
	~BinarySearchST () {
		delete [] ptr;
	}

	bool has (Key key) {
		return ptr[rank (key)].key == key;
	}

	Val get (Key key) {
		return ptr[rank (key)].val;
	}

	void set (Key key, Val val) {
		int num = rank (key);

		if (ptr[num].key == key) {
			ptr[num].val = val;
		}
		else {
			if (n + 1 == capacity) {
				resize (capacity * 2);
			}

			ptr[n++] = Pair (key, val);
			for (int i = n - 1; i > 0; i--) {
				if (ptr[i].key < ptr[i - 1].key) {
					std::swap (ptr[i], ptr[i - 1]);
				}
			}
		}
	}

	void del (Key key) {
		int num = rank (key);

		if (ptr[num].key == key) {
			for (int i = num; i < n - 1; i++) {
				std::swap (ptr[i], ptr[i + 1]);
			}
		}
		
		ptr[n - 1] = Pair<Key, Val> ();

		n--;
	}
};