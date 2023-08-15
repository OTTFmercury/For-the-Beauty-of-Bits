

#include <vector>

using std::vector;

template<typename NumT, NumT (*Fun) (NumT one, NumT two), NumT Identity>
class BinaryIndexedTree {
	private:
	vector<NumT> tree;

	public:

	BinaryIndexedTree () = default;
	BinaryIndexedTree (int n);
	int lowbit (int id);
	void update (int id, NumT num);
	NumT query (int id);
	NumT query (int l, int r);
};

template<typename NumT, NumT (*Fun) (NumT one, NumT two), NumT Identity>
BinaryIndexedTree<NumT, Fun, Identity>::BinaryIndexedTree (int n) {
	tree.resize(n + 1);
}

template<typename NumT, NumT (*Fun) (NumT one, NumT two), NumT Identity>
int BinaryIndexedTree<NumT, Fun, Identity>::lowbit (int id) {
	return id & (-id);
}

template<typename NumT, NumT (*Fun) (NumT one, NumT two), NumT Identity>
void BinaryIndexedTree<NumT, Fun, Identity>::update (int id, NumT num) {
	for (; id <= tree.size(); id += lowbit (id)) {
		tree[id] = Fun (tree[id], num);
	}
}

template<typename NumT, NumT (*Fun) (NumT one, NumT two), NumT Identity>
NumT BinaryIndexedTree<NumT, Fun, Identity>::query (int id) {
	NumT res = Identity;
	for (; id; id -= lowbit (id)) {
		res = Fun (res, tree[id]);
	}
	return res;
}

template<typename NumT, NumT (*Fun) (NumT one, NumT two), NumT Identity>
NumT BinaryIndexedTree<NumT, Fun, Identity>::query (int l, int r) {
	return query (r) - query (l - 1);
}