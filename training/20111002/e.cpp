#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int n, m, c, a[40][40], tot, A, B;
int s[40][40], p[40][40][40][40];

inline int get(int b, int l, int t, int r) {
	return s[t][r] - s[t][l - 1] - s[b - 1][r] + s[b - 1][l - 1];
}

int cut(int b, int l, int t, int r, int c) {
	if (p[b][l][t][r] != -1) return p[b][l][t][r];
	int &ret = p[b][l][t][r];
	ret = 1;
	if (get(b, l, t, r) == c) return ret;
	for (int x = b; x < t; ++ x)
		if (get(b, l, x, r) >= c && get(x + 1, l, t, r) >= c)
			ret = max(ret, cut(b, l, x, r, c) + cut(x + 1, l, t, r, c));
	for (int y = l; y < r; ++ y)
		if (get(b, l, t, y) >= c && get(b, y + 1, t, r) >= c)
			ret = max(ret, cut(b, l, t, y, c) + cut(b, y + 1, t, r, c));
	return ret;
}

int main() {
	while (scanf("%d%d%d", &n, &m, &c) == 3 && (n || m || c)) {
		tot = 0;
		for (int i = 1; i <= n; ++ i)
			for (int j = 1; j <= m; ++ j) {
				scanf("%d", &a[i][j]), tot += a[i][j];
				s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
			}
		memset(p, -1, sizeof(p));
		A = cut(1, 1, n, m, tot - c);
		int l = tot - c, r = tot;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			memset(p, -1, sizeof(p));
			int tmp = cut(1, 1, n, m, mid);
			if (tmp < A) r = mid - 1;
			else l = mid;
		}
		printf("%d %d\n", A, c - tot + l);
	}
	return 0;
}

