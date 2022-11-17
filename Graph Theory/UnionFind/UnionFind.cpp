// Cheer for the most beautiful data structure -- Union-Find!

#include <vector>
#include <numeric>

using namespace std;

template <typename T = int>
class UnionFind {
	private:
	T count;
	vector<T> father;
	vector<T> size {};

	public:

	UnionFind (T n = 1e5);
	int find (T num);
	bool same (T one, T two) {return find (one) == find (two);}
	void merge (T one, T two);
	int howmany () {return count;}
};

template <typename T>
UnionFind<T>::UnionFind (T n = 1e5) {
	father.resize(n);
	size.resize(n);
	count = n;

	iota (father.begin(), father.end(), 0);
}

template <typename T>
int UnionFind<T>::find (T num) {
	vector<int> sons;

	while (num != father[num]) {
		sons.push_back(num);
		num = father[num];
	}
	
	for (int son : sons) {
		father[son] = num;
	}

	return num;
}

template <typename T>
void UnionFind<T>::merge (T one, T two) {
	one = find (one);
	two = find (two);

	if (one == two) {
		return;
	}

	if (size[one] > size[two]) {
		father[two] = one;
		size[one] += size[two];
	}
	else {
		father[one] = two;
		size[two] += size[one];
	}

	count--;
}