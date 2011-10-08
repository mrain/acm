#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

int n, m, C, ans, cnt;
int a[10][20][20];
bool vis[20][20];

void setcolor(int x, int y, int c, int a[][20], int b[][20]) {
	if (x < 0 || y < 0 || x >= n || y >= m || vis[x][y] || a[x][y] != a[0][0]) return;
	vis[x][y] = true;
	b[x][y] = c;
	setcolor(x - 1, y, c, a, b);
	setcolor(x + 1, y, c, a, b);
	setcolor(x, y + 1, c, a, b);
	setcolor(x, y - 1, c, a, b);
}

int getsize(int x, int y, int c, int a[][20]) {
	if (x < 0 || y < 0 || x >= n || y >= m || vis[x][y] || a[x][y] != c) return 0;
	vis[x][y] = true;
	int ret = getsize(x + 1, y, c, a);
	ret += getsize(x, y + 1, c, a);
	ret += getsize(x - 1, y, c, a) + getsize(x, y - 1, c, a);
	return ret + 1;
}

int dfs(int d) {
	memcpy(a[d + 1], a[d], sizeof(a[d]));
	int p = 0;
	for (int c = 1; c <= 6; ++ c) {
		memset(vis, 0, sizeof(vis));
		setcolor(0, 0, c, a[d], a[d + 1]);
		if (d == 4) {
			if (c != C) continue;
			memset(vis, 0, sizeof(vis));
			p = max(p, getsize(0, 0, c, a[d + 1]));
		} else p = max(p, dfs(d + 1));
	}
	return p;
}

int main() {
	while (scanf("%d%d%d", &n, &m, &C) == 3 && (n || m || C)) {
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < m; ++ j)
				scanf("%d", &a[0][i][j]);
		ans = dfs(0);
		cout << ans << endl;
	}
	return 0;
}
