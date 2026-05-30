

#include <algorithm>
#include <vector>

using std::fill;
using std::make_pair;
using std::pair;
using std::vector;

class DancingLinksX {
	private:
	int n;
	int m;
	int Len;
	int cc;
	vector<int> l;
	vector<int> r;
	vector<int> u;
	vector<int> d;
	vector<int> row;
	vector<int> col;
	vector<int> h;
	vector<int> s;

	vector<int> res;
	vector<int> ans;
	bool dance (int deep);

	public:
	DancingLinksX (int n, int m);
	void insert (int R, int C);
	void remove (int C);
	void resume (int C);
	pair<bool, vector<int>> dance ();
};

DancingLinksX::DancingLinksX (int n, int m) : n (n), m (m), Len (n * m + m + 10), l (Len), r (Len), u (Len), d (Len), row (Len), col (Len), h (Len), s (Len), res (Len) {
	for (int i = 0; i <= m; i++) {
		l[i] = i - 1;
		r[i] = i + 1;
		u[i] = d[i] = i;
	}
	l[0] = m;
	r[m] = 0;
	fill (h.begin(), h.end(), -1);
	cc = m;
}

void DancingLinksX::insert (int R, int C) {
	cc++;

	s[C]++;
	row[cc] = R;
	col[cc] = C;
	u[cc] = C;
	d[cc] = d[C];
	u[d[C]] = cc;
	d[C] = cc;

	if (h[R] == -1) {
		h[R] = l[cc] = r[cc] = cc;
	}
	else {
		r[cc] = h[R];
		l[cc] = l[h[R]];
		r[l[h[R]]] = cc;
		l[h[R]] = cc;
	}
}

void DancingLinksX::remove (int C) {
	r[l[C]] = r[C];
	l[r[C]] = l[C];
	for (int i = d[C]; i != C; i = d[i]) {
		for (int j = r[i]; j != i; j = r[j]) {
			u[d[j]] = u[j];
			d[u[j]] = d[j];
			s[col[j]]--;
		}
	}
}

void DancingLinksX::resume (int C) {
	for (int i = u[C]; i != C; i = u[i]) {
		for (int j = l[i]; j != i; j = l[j]) {
			u[d[j]] = j;
			d[u[j]] = j;
			s[col[j]]++;
		}
	}
	r[l[C]] = C;
	l[r[C]] = C;
}

bool DancingLinksX::dance(int deep) {
	if (r[0] == 0) {
		ans.clear();
		for (int i = 0; i < deep; i++) {
			ans.push_back(res[i]);
		}
		return true;
	}

	int c = r[0];
	for (int i = r[0]; i != 0; i = r[i]) {
		if (s[i] < s[c]) {
			c = i;
		}
	}
	remove (c);

	for (int i = d[c]; i != c; i = d[i]) {
		res[deep] = row[i];
		for (int j = r[i]; j != i; j = r[j]) {
			remove (col[j]);
		}
		if (dance (deep + 1)) {
			return true;
		}
		for (int j = l[i]; j != i; j = l[j]) {
			resume (col[j]);
		}
	}
	resume (c);

	return false;
}

pair<bool, vector<int>> DancingLinksX::dance() {
	ans.clear();
	if (dance (0)) {
		return make_pair (true, ans);
	}
	ans.clear();
	return make_pair (false, ans);
}