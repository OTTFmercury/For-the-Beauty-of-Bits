
const int N = 114514;

namespace Cartesian_Tree {
    /*
	require:
		constant : N
	*/

	int top;
	int st[N];
	
	void build (int nums[N], int n, int lson[N], int rson[N]) {
		top = 1;
		st[1] = 1;
		for (int i = 2; i <= n; i++) {
			while (top && (nums[st[top]] > nums[i])) {
				top--;
			}
			if (!top) {
				lson[i] = st[1];
			}
			else {
				lson[i] = rson[st[top]];
				rson[st[top]] = i;
			}
			
			st[++top] = i;
		}
	}
}