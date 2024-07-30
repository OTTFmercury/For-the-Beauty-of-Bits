

#include <algorithm>
#include <array>
#include <complex>
#include <cmath>
#include <vector>

using comp = std::complex<double>;

class FastFourierTransform {
	private:
	long long limit;
	long long l;
	std::vector<long long> change;
	const double pi = std::acos (-1);

	public:
	FastFourierTransform (long long limit, long long l);
	void fft (std::vector<comp> &nums, int flag);
};

FastFourierTransform::FastFourierTransform (long long limit, long long l) : limit (limit), l (l) {
	change.resize(limit);
	for (int i = 0; i < limit; i++) {
		change[i] = (change[i >> 1] >> 1) | ((i & 1) << (l - 1));
	}
}

void FastFourierTransform::fft (std::vector<comp> &nums, int flag) {
	for (int i = 0; i < limit; i++) {
		if (i < change[i]) {
			std::swap (nums[i], nums[change[i]]);
		}
	}
	for (long long mid = 1; mid < limit; mid <<= 1) {
		comp W (std::cos (pi / mid), flag * std::sin (pi / mid));
		for (long long r = mid << 1, j = 0; j < limit; j += r) {
			comp w (1, 0);
			for (long long l = 0; l < mid; l++, w *= W) {
				comp x = nums[j + l];
				comp y = w * nums[j + mid + l];

				nums[j + l] = x + y;
				nums[j + mid + l] = x - y;
			}
		}
	}
}