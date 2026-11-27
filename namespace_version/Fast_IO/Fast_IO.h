
#include <cstdio>
#include <iostream>

#ifdef __unix__
#define getchar getchar_unlocked
#else
#define getchar _getchar_nolock
#endif

namespace Fast_IO {
    template <typename T>
    T read () {
        T res = 0;
        T ch = getchar();
        T op = 1;

        while ((ch < '0' || ch > '9') && ch != EOF) {
            op = (ch == '-' ? -1 : 1);
            ch = getchar ();
        }

        while (ch >= '0' && ch <= '9') {
            res = (res * 10) + (ch - '0');
            ch = getchar ();
        }
        return op * res;
    }

    template <typename T>
    void read (T & res) {
        res = 0;
        T ch = getchar();
        T op = 1;

        while ((ch < '0' || ch > '9') && ch != EOF) {
            op = (ch == '-' ? -1 : 1);
            ch = getchar ();
        }

        while (ch >= '0' && ch <= '9') {
            res = (res * 10) + (ch - '0');
            ch = getchar ();
        }
        res = op * res;
    }
}