

#include <string>
#include <vector>

const int N = 1000010;

namespace Knuth_Morris_Pratt {
    /*
    detail:
        pat should begin with [0]
        
    require:
        class: string, vector
        constant: N
        headfile: string, vector
    */

    using std::string;
    using std::vector;

    void pi_generation (const string & pat, int pi[N]) {
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

    vector<int> match (const string & pat, int pi[N], const string & txt) {
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
}