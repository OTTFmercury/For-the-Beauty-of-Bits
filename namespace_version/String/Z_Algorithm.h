

#include <algorithm>
#include <string>

const int N = 10000010;

namespace Z_Algorithm {
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

    void z_generation (const string &str, int z[N]) {
        z[0] = str.size();
        int l = 0, r = 0;

        for (int i = 1; i < str.size(); i++) {
            if (i < r) {
                z[i] = min (z[i - l], r - i);
            }

            while (i + z[i] < str.size() && str[z[i]] == str[i + z[i]]) {
                z[i]++;
            }

            if (i + z[i] > r) {
                l = i;
                r = i + z[i];
            }
        }
    }

    void match (const string &pat, int z[N], const string &txt, long long res[N]) {
        int l = 0, r = 0;

        for (int i = 0; i < txt.size(); i++) {
            res[i] = 0;
            if (i < r) {
                res[i] = min (z[i - l], r - i);
            }

            while (res[i] < pat.size() && i + res[i] < txt.size() && pat[res[i]] == txt[i + res[i]]) {
                res[i]++;
            }

            if (i + res[i] > r) {
                l = i;
                r = i + res[i];
            }
        }
    }
}