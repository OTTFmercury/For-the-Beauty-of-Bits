// Cheer for the most beautiful data structure -- Union-Find!

#include <vector>
#include <numeric>

using namespace std;

class UnionFind {
	private:
	int count;
	vector<int> father;
	vector<int> size {};

	public:

	UnionFind (int n = 1e5);
	int find (int num);
	bool same (int one, int two) {return find (one) == find (two);}
	void merge (int one, int two);
	int howmany () {return count;}
};

UnionFind::UnionFind (int n) {
	father.resize(n);
	size.resize(n);
	count = n;

	iota (father.begin(), father.end(), 0);
}

int UnionFind::find (int num) {
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

void UnionFind::merge (int one, int two) {
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