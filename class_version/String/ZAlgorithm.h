

#include <algorithm>
#include <string>
#include <vector>

using std::max;
using std::string;
using std::vector;

class ZAlgorithm {
	private:
	string pat;
	vector<int> z;

	public:
	ZAlgorithm () = default;
	ZAlgorithm (string pat);
};

ZAlgorithm::ZAlgorithm (string pat) : pat (pat) {
	z.resize(pat.size());
	int p = 0;
	int k = 1;

	z[0] = pat.size();

	while (p + 1 < pat.size() && pat[p] == pat[p + 1]) {
		p++;
	}
	z[1] = p;

	for (int i = 2; i < pat.size(); i++) {
		p = k + z[k] - 1;
		int l = z[i - k];

		if (i + l <= p) {
			z[i] = l;
		}
		else {
			int j = max (0, p - i + 1);
			while (i + j < pat.size() && pat[i + j] == pat[j]) {
				j++;
			}
			z[i] = j;
			k = i;
		}
	}
}