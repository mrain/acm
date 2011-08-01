#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;

int tests, n;
char a[3000];
int f[300][300][2];

int cmp(int a1, int b1, int a2, int b2) {
	while (a1 < b1 && a[a1] == '0') ++ a1;
	while (a2 < b2 && a[a2] == '0') ++ a2;
	int l1 = b1 - a1 + 1, l2 = b2 - a2 + 1;
	if (l1 != l2) return l1 > l2 ? 1 : -1;
	for (int i = 0; i < l2; ++ i)
		if (a[a1 + i] != a[a2 + i])
			return a[a1 + i] > a[a2 + i] ? 1 : -1;
	return 0;
}

int main() {
	scanf("%d", &tests);
	while (tests --) {
		scanf("%d %s", &n, a);
		memset(f, 0xFF, sizeof(f));
		for (int i = 0; i < n; ++ i)
			f[0][i][0] = 0;
		int ans = 0;
		for (int j = 0; j < n; ++ j)
			for (int i = 0; i <= j; ++ i)
				for (int k = 0; k < i; ++ k) {
					if (f[k][i - 1][0] != -1 && cmp(k, i - 1, i, j) == -1)
						f[i][j][1] = max(f[i][j][1], f[k][i - 1][0] + 1);
					if (f[k][i - 1][1] != -1 && cmp(k, i - 1, i, j) == 1)
						f[i][j][0] = max(f[i][j][0], f[k][i - 1][1] + 1);
				}
		for (int i = 0; i < n; ++ i)
			ans = max(ans, max(f[i][n - 1][0], f[i][n - 1][1]));
		cout << ans << endl;
	}
	return 0;
}

