
#include <string>

const int N = 514514;
const int AlphabetSize = 26;

namespace Palindromic_Tree {
    /*
    detail:
        str begins with [1]
        
    require:
        class: string
        constant: N, AlphabetSize
        headfile: string
    */

    using std::string;

    void init (int fail[N], int len[N], int & tot, string & str) {
        tot = 1;
        fail[0] = 1;
        len[1] = -1;
        str = " ";
    }

    int fail_jump (int fail[N], int len[N], string & str, int u, int i) {
        while (i - len[u] - 1 <= 0 || str[i - len[u] - 1] != str[i]) {
            u = fail[u];
        }
        return u;
    }

    void add (int tree[N][AlphabetSize], int fail[N], int len[N], int & cc, int & now, int & tot, string & str, char ch, int trans[N]) {
        /*
        detail:
            gradually put ch to the end of str
        */

        cc++;
        str += ch;
        int pos = fail_jump (fail, len, str, now, cc);
        int num = ch - 'a';
        if (!tree[pos][num]) {
            tot++;
            fail[tot] = tree[fail_jump (fail, len, str, fail[pos], cc)][num];
            tree[pos][num] = tot;
            len[tot] = len[pos] + 2;
        }
        now = tree[pos][num];
    }
}