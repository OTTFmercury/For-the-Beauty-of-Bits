

#include <string>
#include <vector>

using std::string;
using std::vector;

class KMP {
	private:
	string pat;
	vector<int> pi;

	public:
	KMP () = default;
	KMP (string pat);
	vector<int> getPi () {return pi;}
	vector<int> kmp (string txt);
};

KMP::KMP (string pat) : pat (pat) {
	pi.resize(pat.size());
	for (int i = 1, j = 0; i < pat.size(); i++) {
		while (j && pat[i] != pat[j]) {
			j = pi[j - 1];
		}
		if (pat[i] == pat[j]) {
			j++;
		}
		pi[i] = j;
	}
}

vector<int> KMP::kmp (string txt) {
	vector<int> res;
	for (int i = 0, j = 0; i < txt.size(); i++) {
		while (j && txt[i] != pat[j]) {
			j = pi[j - 1];
		}
		if (txt[i] == pat[j]) {
			j++;
		}
		if (j == pat.size()) {
			res.push_back(i - j + 2);
			j = pi[j - 1];
		}
	}
	return res;
}