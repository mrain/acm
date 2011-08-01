#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {-1, 0, 1, 0};
int n, m, tests, sx, sy, tot;
int a[310][310];
bool vis[310][310], vis2[310][310];

void dfs(int x, int y) {
	for (int i = 0; i < 4; ++ i) {
		int p = x + dx[i], q = y + dy[i];
		if (!vis[p][q]) {
			vis[p][q] = true;
			if (p > 0 && q > 0 && p <= n && q <= m && !a[p][q])
				dfs(p, q);
		}
	}
}

void dfs2(int x, int y) {
	for (int i = 0; i < 4; ++ i) {
		int p = x + dx[i], q = y + dy[i];
		if (p > 0 && q > 0 && p <= n && q <= m && !vis2[p][q]) {
			vis2[p][q] = true;
			tot += a[p][q];
			if (vis[p][q]) -- tot;
			else dfs2(p, q);
		}
	}
}

int main() {
	scanf("%d", &tests);
	while (tests --) {
		memset(vis, 0, sizeof(vis));
		memset(a, 0, sizeof(a));
		scanf("%d%d", &n, &m);
		tot = 0;
		for (int i = 1; i <= n; ++ i)
			for (int j = 1; j <= m; ++ j) {
				scanf("%d", &a[i][j]);
				if (a[i][j] == -1)
					sx = i, sy = j;
			}
		dfs(sx, sy);
		memset(vis2, 0, sizeof(vis2));
		for (int i = 1; i <= n; ++ i) {
			dfs2(i, 0); dfs2(i, m + 1);
			if (vis[i][0] || vis[i][m + 1]) {
				puts("Ali Win");
				goto CONTINUE;
			}
		}
		for (int i = 1; i <= m; ++ i) {
			dfs2(0, i); dfs2(n + 1, i);
			if (vis[0][i] || vis[n + 1][i]) {
				puts("Baba Win");
				goto CONTINUE;
			}
		}
		puts(((tot & 1) == 1) ? "Ali Win" : "Baba Win");
CONTINUE:;
	}
	return 0;
}

