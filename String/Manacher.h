

#include <algorithm>
#include <string>
#include <vector>

using std::min;
using std::string;
using std::vector;

template<typename ResT>
class Manacher {
	private:
	string str;

	public:

	Manacher (string str) : str (str) {}
	void sthForStr (char put = '#');
	vector<ResT> manacher ();
};

template<typename ResT>
void Manacher<ResT>::sthForStr (char put) {
	string res = "";
	for (char ch : str) {
		res += put;
		res += ch;
	}
	res += put;
	str = res;
}

template<typename ResT>
vector<ResT> Manacher<ResT>::manacher () {
	int l = 0, r = -1;
	vector<ResT> res;
	
	for (int i = 0; i < str.size(); i++) {
		int k = ((i > r) ? 1 : min (res[l + r - i], r - i + 1));

		while (i - k >= 0 && i + k < str.size() && str[i - k] == str[i + k]) {
			k++;
		}
		k--;

		res.push_back(k);

		if (i + k > r) {
			r = i + k;
			l = i - k;
		}
	}

	return res;
}