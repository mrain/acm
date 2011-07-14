#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <cmath>
#include <cctype>
using namespace std;

int l, n, a[1000010];
int tests;
long long sum[1000010];

inline long long get(int i, int j) {
	if (i) return sum[j] - sum[i];
	else return sum[j];
}

inline long long calc(int i) {
	long long ret = 0;
	if (i * 2 < n) {
		long long tmp = (long long)i * a[i];
		ret = tmp + a[i] - get(0, i) + (get(i + 1, i + i + 1) - tmp) + a[i];
	}
	if (i >= n / 2) {
		long long tmp = (long long)(n - i - 1) * a[i];
		ret = max(ret, tmp - get(i + 1, n - 1) + (tmp - get(i - (n - i - 1) - 1, i - 1)) + (l - a[i]));
	}
	return ret;
}

int main() {
	scanf("%d", &tests);
	while (tests --) {
		scanf("%d%d", &l, &n);
		long long ans1 = 0, ans2 = 0;
		for (int i = 0; i < n; ++ i) {
			scanf("%d", &a[i]);
			ans1 = max(ans1, (long long)min(a[i], l - a[i]));
			ans2 = max(ans2, (long long)max(a[i], l - a[i]));
		}
		cout << ans1 << ' ' << ans2 << endl;
	}
	return 0;
}

