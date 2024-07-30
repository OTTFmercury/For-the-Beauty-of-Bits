

#include <algorithm>
#include <utility>
#include <vector>

using std::make_pair;
using std::sort;
using std::vector;

class SuffixArray {
	private:
    int n;
	vector<int> chs;
	vector<int> rk;
	vector<int> sa;
	vector<int> ht;
	
	public:
	
	SuffixArray () = default;
	SuffixArray (vector<int> chs) : n (chs.size() - 1), chs (chs) {
		rk.resize((chs.size() + 10) * 2);
		sa.resize(chs.size() + 10);
		ht.resize(chs.size());
	}
	
	auto getRk () {
		return rk;
	}
	auto getSa () {
		return sa;
	}
	auto getHt () {
		return ht;
	}
	
	int getSize () {
		return chs.size() - 1;
	}
	
	void initSa () {
		if (n == 1) {
			rk[1] = sa[1] = 1;
            return;
		}
		
		for (int i = 1; i <= n; i++) {
			rk[i] = chs[i];
			sa[i] = i;
		}
		
		for (int i = 1; i < n; i *= 2) {
			auto toPair = [&] (int id) {
				return make_pair (rk[id], rk[id + i]);
			};
			sort (sa.begin() + 1, sa.begin() + n + 1, [&] (int one, int two) {return toPair (one) < toPair (two);});
			
			vector<int> tmp (rk.size());
			for (int j = 1, k = 0; j <= n; j++) {
				tmp[sa[j]] = (toPair (sa[j - 1]) == toPair (sa[j]) ? k : ++k);
			}
			rk = tmp;
		}
	}
	
	void initHt () {
		for (int i = 1, j = 0; i <= n; i++) {
			j -= (j > 0);
			while (chs[i + j] == chs[sa[rk[i] - 1] + j]) {
				j++;
			}
			ht[rk[i]] = j;
		}
	}
};