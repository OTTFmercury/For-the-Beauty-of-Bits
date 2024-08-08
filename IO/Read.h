

template <typename T>
T read () {
    T res = 0;
	T ch = getchar();
	T op = 1;

    while (!isdigit (ch) && ch != EOF) {
		op = (ch == '-' ? -1 : 1);
        ch = getchar ();
	}

    while (isdigit (ch)) {
        res = (res * 10) + (ch - '0');
        ch = getchar ();
    }
    return op * res;
}

template <typename T>
void read (T& num) {
    T res = 0;
	T ch = getchar();
	T op = 1;

    while (!isdigit (ch) && ch != EOF) {
		op = (ch == '-' ? -1 : 1);
        ch = getchar ();
	}

    while (isdigit (ch)) {
        res = (res * 10) + (ch - '0');
        ch = getchar ();
    }
    num = op * res;
}

class Read {
	public:
	Read operator>> (auto& other) {
		read (other);
		return (*this);
	}
};

Read in;