

#include <algorithm>
#include <string>

const int N = 1000010;

namespace Manacher {
    /*
    detail:
        str should begin with [0]
        
    require:
        class: string
        constant: N
        function: min
        headfile: algorithm, string
    */

    using std::string;
    using std::min;

    string split_string_with_character (string str, char splitChar) {
        string res = "";
        for (auto ch : str) {
            res += splitChar;
            res += ch;
        }
        res += splitChar;
        return res;
    }

    void solve (string str, int res[N]) {
        int l = 0, r = -1;
	
        for (int i = 0; i < str.size(); i++) {
            if (i <= r) {
                res[i] = min (res[l + r - i], r - i + 1);
            }
            else {
                res[i] = 1;
            }

            while (i - res[i] >= 0 && i + res[i] < str.size() && str[i - res[i]] == str[i + res[i]]) {
                res[i]++;
            }
            res[i]--;

            if (i + res[i] > r) {
                l = i - res[i];
                r = i + res[i];
            }
        }
    }
}