

#include <cctype>
#include <cstdio>

template <typename T>
T read () {
    T res = 0;
	T ch = getchar();

    while (!isdigit (ch) && ch != EOF) {
        ch = getchar ();
	}

    while (isdigit (ch)) {
        res = (res * 10) + (ch - '0');
        ch = getchar ();
    }
    return res;
}