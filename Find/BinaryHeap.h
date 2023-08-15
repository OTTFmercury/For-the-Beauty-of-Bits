

#include <memory>
#include <optional>
#include <tuple>
#include <stack>

using std::shared_ptr;
using std::optional;
using std::stack;

template <typename Key, typename Val>
class BinaryHeap {
	private:
	class Node {
		public:
		Key key;
		stack<Val> vals {};

		shared_ptr<Node> l, r;
		
		int num;
		Node () = default;
		Node (Key key, Val val, int num) : key (key), num (num) {
			vals.push(val);
		}
	};

	shared_ptr<Node> root;
	
	int size (shared_ptr<Node> node) {
		if (node == nullptr) {
			return 0;
		}
		else {
			return node->num;
		}
	}
	
	optional<Val> get (Key key, shared_ptr<Node> node) {
		if (node == nullptr) {
			return {};
		}
		else if (key < node->key) {
			return get (key, node->l);
		}
		else if (key > node->key) {
			return get (key, node->r);
		}
		else {
			return node->vals.top();
		}
	}

	shared_ptr<Node> put (Key key, Val val, shared_ptr<Node> node) {
		if (node == nullptr) {
			return shared_ptr<Node> (new Node (key, val, 1));
		}

		if (key < node->key) {
			node->l = put (key, val, node->l);
		}
		else if (key > node->key) {
			node->r = put (key, val, node->r);
		}
		else {
			node->vals.push(val);
		}

		node->num = size (node->l) + size (node->r) + node->vals.size();

		return node;
	}

	shared_ptr<Node> min (shared_ptr<Node> node) {
		if (node->l == nullptr) {
			return node;
		}
		return min (node->l);
	}

	shared_ptr<Node> max (shared_ptr<Node> node) {
		if (node->r == nullptr) {
			return node;
		}
		return max (node->r);
	}

	optional<Key> pre (Key key, shared_ptr<Node> node) {
		if (node == nullptr) {
			return {};
		}

		if (key < node->key) {
			if (node->l == nullptr) {
				return node->key;
			}
			return pre (key, node->l);
		}
		else if (key > node->key) {
			if (node->r == nullptr) {
				return node->key;
			}
			return pre (key, node->r);
		}
		else {
			if (node->l == nullptr) {
				return {};
			}
			return max (node->l)->key;
		}
	}

	optional<Key> nxt (Key key, shared_ptr<Node> node) {
		if (node == nullptr) {
			return {};
		}

		if (key < node->key) {
			if (node->l == nullptr) {
				return node->key;
			}
			return pre (key, node->l);
		}
		else if (key > node->key) {
			if (node->r == nullptr) {
				return node->key;
			}
			return pre (key, node->r);
		}
		else {
			if (node->r == nullptr) {
				return {};
			}
			return min (node->r)->key;
		}
	}

	optional<shared_ptr<Node>> select (int k, shared_ptr<Node> node) {
		if (node == nullptr) {
			return {};
		}

		int t = size (node->l) + 1;
		if (k < t) {
			return select (k, node->l);
		}
		else if (k > t) {
			return select (k - t, node->r);
		}
		else {
			return node;
		}
	}

	int rank (Key key, shared_ptr<Node> node) {
		if (node == nullptr) {
			return -1;
		}

		if (key < node->key) {
			return rank (key, node->l);
		}
		else if (key > node->key) {
			return size (node->l) + 1 + rank (key, node->r);
		}
		else {
			return size (node->l) + 1;
		}
	}

	optional<shared_ptr<Node>> del (Key key, shared_ptr<Node> node) {
		if (node == nullptr) {
			return {};
		}

		if (key < node->key) {
			auto t = del (key, node->l);
			if (t.has_value()) {
				node->l = t.value();
			}
			else {
				node->l = nullptr;
			}
		}
		else if (key > node->key) {
			auto t = del (key, node->r);
			if (t.has_value()) {
				node->r = t.value();
			}
			else {
				node->r = nullptr;
			}
		}
		else {
			if (node->vals.size() != 1) {
				node->vals.pop();
			}
			else {
				if (node->l == nullptr) {
					return node->r;
				}
				else if (node->r == nullptr) {
					return node->l;
				}
				else {
					auto t = node;
					node = min (t->r);
					cout << node->key << endl;

					auto tt = del (node->key, t->r);
					if (tt.has_value()) {
						node->r = tt.value();
					}
					else {
						node->r = nullptr;
					}

					node->l = t->l;
				}
			}
		}

		node->num = size (node->l) + size (node->r) + node->vals.size();

		return node;
	}

	public:

	int size () {
		return size (root);
	}

	optional<Val> get (Key key) {
		return get (key, root);
	}

	void put (Key key, Val val) {
		root = put (key, val, root);
	}

	shared_ptr<Node> min () {
		return min (root);
	}

	shared_ptr<Node> max () {
		return max (root);
	}

	optional<Key> pre (Key key) {
		return pre (key, root);
	}

	optional<Key> nxt (Key key) {
		return nxt (key, root);
	}

	optional<shared_ptr<Node>> select (int k) {
		return select (k, root);
	}

	int rank (Key key) {
		return rank (key, root);
	}

	void del (Key key) {
		auto t = del (key, root);

		if (t.has_value()) {
			root = t.value();
		}
		else {
			root = nullptr;
		}
	}

};