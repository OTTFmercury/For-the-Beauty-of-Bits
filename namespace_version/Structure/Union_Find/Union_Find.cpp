

const int Size = 1000005;

namespace Union_Find {
    /*
    require:
        constant: Size
    */

    void init (int dad[Size], int size[Size], int n) {
        for (int i = 1; i <= n; i++) {
            dad[i] = i;
            size[i] = 1;
        }
    }

    int find (int dad[Size], int id) {
        if (dad[id] == id) {
            return id;
        }

        dad[id] = find (dad, dad[id]);
        return dad[id];
    }

    void merge (int dad[Size], int size[Size], int one, int two) {
        one = find (dad, one);
        two = find (dad, two);

        if (one == two) {
            return;
        }

        if (size[one] < size[two]) {
            dad[one] = two;
            size[two] += size[one];
        }
        else {
            dad[two] = one;
            size[one] += size[two];
        }
    }

    bool same (int dad[Size], int one, int two) {
        return find (dad, one) == find (dad, two);
    }
}