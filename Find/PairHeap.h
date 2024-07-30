

#include <algorithm>
#include <array>

using std::array;
using std::swap;

template <typename T, int N>
class PairHeap {
    private:
    int n;
	array<int, N> root;
	array<int, N> kid;
	array<int, N> bro;

	int merge (int x);

    public:
	array<T, N> nodes;
    PairHeap () = default;
    PairHeap (int n) : n (n) {
		for (int i = 1; i <= n; i++) {
            root[i] = i;
        }
	}
	
	int find (int num) {return (root[num] == num) ? num : root[num] = find (root[num]);}
	int meld (int x, int y);
	int pop (int x);
};

template <typename T, int N>
int PairHeap<T, N>::meld (int x, int y) {
	if (x == 0) {
		return y;
	}
	if (y == 0) {
		return x;
	}

	if (nodes[x] > nodes[y]) {
		swap (x, y);
	}

	bro[y] = kid[x];
	kid[x] = y;

	root[x] = root[y] = x;

	return x;
}

template <typename T, int N>
int PairHeap<T, N>::merge (int x) {
	if (x == 0 || bro[x] == 0) {
		return x;
	}

	int one = bro[x];
	int two = bro[one];

	bro[x] = bro[one] = 0;

	return meld (merge (two), meld (x, one));
}

template <typename T, int N>
int PairHeap<T, N>::pop(int x) {
	x = find (x);
	int t = merge (kid[x]);
	root[x] = t;
	root[t] = t;
	return t;
}