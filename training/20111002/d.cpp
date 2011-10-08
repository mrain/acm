#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;
#define two(x) (1<<(x))

bool cover[200][200];
int n, x[200], y[200], r[200], c[200];
signed char res[two(24)];

inline int sqr(int a) { return a * a; }

int dist(int i, int j) {
	return sqr(x[i] - x[j]) + sqr(y[i] - y[j]);
}

int dfs(int st) {
	if (res[st] != -1) return res[st];
	int cnt = 0, ret = 0, mask = 0;
	for (int i = 0; i < n; ++ i)
		if (st & two(i)) {
			++ cnt;
			bool flag = true;
			for (int j = i + 1; j < n; ++ j)
				if ((st & two(j)) && cover[j][i]) {
					flag = false;
					break;
				}
			if (flag) mask |= two(i);
		}
	for (int i = n - 1; i >= 0; -- i) {
		if ((two(i) & mask) == 0) continue;
		for (int j = i - 1; j >= 0; -- j) {
			if ((two(j) & mask) == 0) continue;
			if (c[i] != c[j]) continue;
			ret = max(ret, dfs(st ^ two(i) ^ two(j)) + 2);
			if (ret == cnt) break;
		}
		if (ret == cnt) break;
	}
	return res[st] = ret;
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; ++ i)
			scanf("%d%d%d%d", x + i, y + i, r + i, c + i);
		reverse(x, x + n);
		reverse(y, y + n);
		reverse(r, r + n);
		reverse(c, c + n);
		memset(cover, 0, sizeof(cover));
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < i; ++ j)
				if (dist(i, j) < sqr(r[i] + r[j])) {
					cover[i][j] = true;
//					cout << dist(i, j) << ' ' << sqr(r[i] + r[j]) << ' ' << i << ' ' << j << endl;
				}
		memset(res, -1, sizeof(res));
		printf("%d\n", dfs(two(n) - 1));
	}
	return 0;
}
