

#include <algorithm>
#include <string>
#include <utility>

const int N = 114514 << 1;

namespace Suffix_Array {
    /*
    detail:
        chs should begin with [0]

    require:
        class: string
        constant: N
        headfile: algorithm string utility
        function: make_pair, sort
    */

    using std::make_pair;
    using std::sort;
    using std::string;

    int tmp[N];
    void init_sa (int chs[N], int rk[N << 1], int sa[N], int n) {
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
			sort (sa + 1, sa + n + 1, [&] (int one, int two) {return toPair (one) < toPair (two);});
			
			for (int j = 1, k = 0; j <= n; j++) {
				tmp[sa[j]] = (toPair (sa[j - 1]) == toPair (sa[j]) ? k : ++k);
			}
            for (int j = 1; j <= n; j++) {
				rk[j] = tmp[j];
			}
		}
	}
	
	void init_ht (int chs[N], int rk[N << 1], int sa[N], int ht[N], int n) {
		for (int i = 1, j = 0; i <= n; i++) {
			j -= (j > 0);
			while (chs[i + j] == chs[sa[rk[i] - 1] + j]) {
				j++;
			}
			ht[rk[i]] = j;
		}
	}

    void init_chs (string str, int chs[N]) {
        /*
        detail:
            str should begin with [0]
        */

        for (int i = 0; i < str.size(); i++) {
            chs[i + 1] = str[i];
        }
    }
}