
const int Maxn = 1e6;

namespace Log2 {
    /*
    require:
        constant: Maxn
    */
    
    int log2[Maxn];
    
    void init () {
        for (int i = 2; i < Maxn; i++) {
            log2[i] = log2[i / 2] + 1;
        }
    }
}