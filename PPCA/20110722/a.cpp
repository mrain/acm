#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

const int inf = 0x2FFFFFF;
int n, a[2010], b[2010];
int f[2010][2010];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d", a + i);
	for (int i = 0; i < n; ++ i) scanf("%d", b + i), b[i] += a[i];
	for (int i = 0; i < n; ++ i) {
		int cur = 0, ans = inf;
		for (int j = i; j < n; ++ j) {
			if (cur > 0) cur = a[j];
			else cur += a[j];
			if (cur < ans) ans = cur;
			f[i][j] = ans;
		}
	}
	int ans = -inf;
	for (int i = 0; i < n; ++ i) {
		int cnt = b[i];
		for (int j = i + 1; j < n; ++ j) {
			cnt += b[j];
			if (j - i < 2) continue;
			if (cnt - f[i + 1][j - 1] > ans)
				ans = cnt - f[i + 1][j - 1];
		}
	}
	cout << ans << endl;
	return 0;
}

