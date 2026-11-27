
const int N = 15;

namespace Combination_Number {
    /*
    option:
        define: USE_MOD, then, constant: Mod
    require:
        constant: N
    */

    int C[N][N];

    void init () {
        C[0][0] = 1;
        for (int i = 1; i < N; i++) {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++) {
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            }
        }
    }

    #ifdef USE_MOD
    void init_mod () {
        C[0][0] = 1;
        for (int i = 1; i < N; i++) {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++) {
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % Mod;
            }
        }
    }
    #endif
}