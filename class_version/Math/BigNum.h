#include <algorithm>
#include <compare>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "FastFourierTransform.h"

class BigNum {
    private:
    static const int Base = 100;
    bool op = true;
    int len;
    std::vector<long long> nums;

    void forPlus ();
    void forMult ();

    public:

    BigNum (long long n = 0);
    BigNum (std::string str);

	auto operator<=> (const BigNum other) const;

    const BigNum operator- () const;
    void operator+= (const BigNum other);
    void operator-= (const BigNum other);
    void operator*= (const BigNum other);
	void operator/= (const BigNum other);
	void operator%= (const BigNum other);
    const BigNum operator+ (const BigNum other) const;
    const BigNum operator- (const BigNum other) const;
    const BigNum operator* (const BigNum other) const;
	const BigNum operator/ (const BigNum other) const;
	const BigNum operator% (const BigNum other) const;
    const std::pair<BigNum, BigNum> divAndMod (const BigNum other) const;
	
	friend std::ostream &operator << (std::ostream &output, const BigNum &num);
	friend std::istream &operator >> (std::istream &input, BigNum &num);
};

auto BigNum::operator<=> (const BigNum other) const {
	if (op && (!other.op)) {
		return std::strong_ordering::greater;
	}
	if (!op && other.op) {
		return std::strong_ordering::less;
	}

	if (len > other.len) {
		return std::strong_ordering::greater;
	}
	if (len < other.len) {
		return std::strong_ordering::less;
	}

	for (int i = len; i >= 1; i--) {
		if (nums[i] > other.nums[i]) {
			return std::strong_ordering::greater;
		}
		if (nums[i] < other.nums[i]) {
			return std::strong_ordering::less;
		}
	}
	return std::strong_ordering::equal;
}

void BigNum::forPlus () {
    for (int i = 1; i < len; i++) {
        nums[i + 1] += nums[i] / Base;
        nums[i] %= Base;
    }
    while (nums[len] / Base) {
        nums.push_back(nums[len] / Base);
        nums[len] %= Base;
        len++;
    }
    while (nums[len] == 0) {
        len--;
    }
	nums.resize(len + 1);
}

void BigNum::forMult () {
    for (int i = 1; i < len; i++) {
        while (nums[i] < 0) {
            nums[i] += Base;
            nums[i + 1] -= 1;
        }
    }

    while (nums[len] == 0 && len != 1) {
        len--;
    }
    nums.resize(len + 1);

    if (nums[len] < 0) {
        for (int i = 1; i <= len; i++) {
            nums[i] = -nums[i];
        }
        forMult ();
        op = !op;
    }
}

BigNum::BigNum (long long n) {
    if (n < 0) {
        op = false;
        n = -n;
    }
	if (n == 0) {
		nums.resize(2);
    	len = 1;
		return;
	}

    nums.resize(1);
    len = 0;
    while (n) {
        nums.push_back(n % Base);
        len++;
        n /= Base;
    }
}

BigNum::BigNum (std::string str) {
    if (str[0] == '-') {
        op = false;
        str = str.substr(1);
    }
    
    nums.resize(1);
	len = 0;
	int num = 0;
	int base = 1;
    for (int i = str.size() - 1, j = 1; i >= 0; i--) {
        num += base * (str[i] - '0');
		base *= 10;

		if (base == Base || i == 0) {
			nums.push_back(num);
			len++;
			num = 0;
			base = 1;
		}
    }
}

const BigNum BigNum::operator- () const {
    BigNum other = *this;
    other.op = !op;
    return other;
}

void BigNum::operator+= (const BigNum other) {
    if (op != other.op) {
        (*this) -= (-other);
        return;
    }

    int newLen = std::max (this->len, other.len);
    this->nums.resize(newLen + 1);
    len = newLen;
    for (int i = 1; i <= other.len; i++) {
        nums[i] += other.nums[i];
    }
    forPlus ();
}

void BigNum::operator-= (const BigNum other) {
    if (op != other.op) {
        (*this) += -other;
        return;
    }

    int newLen = std::max (this->len, other.len);
    this->nums.resize(newLen + 1);
    len = newLen;

    for (int i = 1; i <= other.len; i++) {
        nums[i] -= other.nums[i];
    }
    forMult ();
}

void BigNum::operator*= (const BigNum other) {
    std::vector<comp> one;
	for (int i = 1; i < nums.size(); i++) {
		one.push_back(nums[i]);
	}

	std::vector<comp> two;
	for (int i = 1; i < other.nums.size(); i++) {
		two.push_back(other.nums[i]);
	}

	long long limit = 1;
	long long l = 0;
	while (limit <= one.size() + two.size()) {
		limit <<= 1;
		l++;
	}

	one.resize(limit);
	two.resize(limit);
	FastFourierTransform fft(limit, l);
	fft.fft(one, 1);
	fft.fft(two, 1);

	for (int i = 0; i < limit; i++) {
		one[i] *= two[i];
	}

	fft.fft(one, -1);

	nums.resize(1);
	for (int i = 0; i < limit; i++) {
		nums.push_back(one[i].real() / limit + 0.5);
	}
	len = limit;
	forPlus();
}

void BigNum::operator/= (const BigNum other) {
    (*this) = (*this) / other;
}

void BigNum::operator%= (const BigNum other) {
    (*this) = (*this) % other;
}

const BigNum BigNum::operator+ (const BigNum other) const {
    BigNum res = (*this);
    res += other;
    return res;
}

const BigNum BigNum::operator- (const BigNum other) const {
    BigNum res = (*this);
    res -= other;
    return res;
}

const BigNum BigNum::operator* (const BigNum other) const {\
    BigNum res = (*this);
	res *= other;
    return res;
}

const BigNum BigNum::operator/ (const BigNum other) const {
    return divAndMod (other).first;
}

const BigNum BigNum::operator% (const BigNum other) const {
    return divAndMod (other).second;
}

const std::pair<BigNum, BigNum> BigNum::divAndMod (const BigNum other) const {
	bool judge = true;
	if (op != other.op) {
		judge = false;
	}

	BigNum num = (*this);
	BigNum by = other;
    BigNum div = 0;

	if (num < 0) {
		num = -num;
	}
	if (by < 0) {
		by = -by;
	}

	if (num < by) {
		return {0, (*this)};
	}
	
	std::vector<BigNum> twos;
    twos.push_back(1);
    for (int i = 1; i <= 3322; i++) {
        twos.push_back(*twos.rbegin() * 2);
    }

    for (auto it = twos.rbegin(); it != twos.rend(); it++) {
        if (num >= *it * by) {
            num -= *it * by;
            div += *it;
        }
    }

	if (!judge) {
		div = -div;
		num = -num;
	}

	return {div, num};
}

std::ostream &operator << (std::ostream &output, const BigNum &num) {
	if (num.op == false) {
		putchar ('-');
	}
	for (int i = num.len; i >= 1; i--) {
		if (i != num.len) {
			for (int j = num.Base / 10; j > 1; j /= 10) {
				if (num.nums[i] < j) {
					std::cout << '0';
				}
			}
		}
		std::cout << num.nums[i];
	}
	return output;
}

std::istream &operator >> (std::istream &input, BigNum &num) {
	std::string str;
	std::cin >> str;
	num = str;
	return input;
}