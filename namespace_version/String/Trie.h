

constexpr int N = 3000010;
constexpr int Alphabet = 70;

namespace Trie {
    /*
    detail:
        str should begin with [1]

    require:
        constant: N
    */

    void insert (int tree[N][Alphabet], int stop[N], int cc[N], int & tot, int str[N], int len) {
        int num = 0;
        for (int i = 1; i <= len; i++) {
            auto ch = str[i];
            if (!tree[num][ch]) {
                tot++;
                tree[num][ch] = tot;
            }
            num = tree[num][ch];
            cc[num]++;
        }
        stop[num]++;
    }

    int query (int tree[N][Alphabet], int cc[N], int str[N], int len) {
        int num = 0;
        for (int i = 1; i <= len; i++) {
            auto ch = str[i];
            if (!tree[num][ch]) {
                return 0;
            }
            num = tree[num][ch];
        }
        return cc[num];
    }
}