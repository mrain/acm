#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <cassert>
#include <vector>
#include <sstream>
using namespace std;

int T, n, m;
int a[10010];

long long calc(int i, int k) {
	long long ret = k;	
	for (int j = 0; j < i; ++ j) {
		ret += ((long long)(k - 1) * (long long)a[i]) / a[j] + 1;
	}
	for (int j = i + 1; j < n; ++ j) {
		ret += ((long long)(k - 1) * (long long)a[i] - 1) / a[j] + 1;
	}
	return ret;
}

int bsearch(int i, int N) {
	long long l = 0, r = N;
	while (r - l > 1) {
		int mid = (r + l) / 2;
		long long f = calc(i, mid);
		if (f < 0) assert(1 == 0);
		if (f <= N) l = mid;
		else r = mid - 1;
	}
	if (calc(i, r) <= N) return r;
	else return l;
}

int main() {
	cin >> T;
	for (int t = 1; t <= T; ++ t) {
		cin >> n >> m;
		for (int i = 0; i < n; ++ i)
			cin >> a[i];
		//sort(a, a + n);

		for (int i = 0; i < n; ++ i) {
			// test whether answer is i
			int p = bsearch(i, m);
			//cout << i << ' ' << p << ' ' << calc(i, p) << endl;
			if (calc(i, p) == m) {
				printf("Case #%d: %d\n", t, i + 1);
				break;
			}
		}
	}
    return 0;
}
