

#include <queue>
#include <string>

const int N = 1145;
const int AlphabetSize = 26;

namespace Aho_Corasick_Automaton {
    /*
    detail:
        str should begin with [0]

    require:
        class: queue, string
        constant: N, AlphabetSize
        headfile: queue, string
    */

    using std::queue;
    using std::string;

    void insert (int tree[N][AlphabetSize], int stop[N], int & tot, string str) {
        int num = 0;
        for (char ch : str) {
            if (!tree[num][ch - 'a']) {
                tot++;
                tree[num][ch - 'a'] = tot;
            }
            num = tree[num][ch - 'a'];
        }
        stop[num]++;
    }

    void fail_generation (int tree[N][AlphabetSize], int fail[N]) {
        queue<int> q;
        for (int i = 0; i < AlphabetSize; i++) {
            if (tree[0][i]) {
                fail[tree[0][i]] = 0;
                q.push(tree[0][i]);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < AlphabetSize; i++) {
                if (tree[u][i]) {
                    fail[tree[u][i]] = tree[fail[u]][i];
                    q.push(tree[u][i]);
                }
                else {
                    tree[u][i] = tree[fail[u]][i];
                }
            }
        }
    }

    long long query (int tree[N][AlphabetSize], int stop[N], int fail[N], string str, int vis[N], int nowvis) {
        /*
        detail:
            nowvis++ before calling    
        */
        
        int id = 0;
        int res = 0;
        for (auto ch : str) {
            id = tree[id][ch - 'a'];
            for (int j = id; j && vis[j] != nowvis; j = fail[j]) {
                res += stop[j];
                vis[j] = nowvis;
            }
        }
        return res;
    }
}