#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {-1, 0, 1, 0};

char a[1010][1010];
int f[1010][1010], d[1010][1010];
int n, m, jx, jy, fx, fy;
typedef pair<int, int> PII;
queue <PII> q;

void bfs() {
	while (!q.empty()) {
		int x = q.front().first, y = q.front().second; q.pop();
		for (int k = 0; k < 4; ++ k) {
			int i = x + dx[k], j = y + dy[k];
			if (i < 0 || j < 0 || i >= n || j >= m || a[i][j] == '#' || f[i][j] != -1) continue;
			f[i][j] = f[x][y] + 1;
			q.push(make_pair(i, j));
		}
	}
}

void bfs2() {
	if (jx == 0 || jy == 0 || jx == n - 1 || jy == n - 1) {
		puts("1");
		return;
	}
	while (!q.empty()) q.pop();
	memset(d, -1, sizeof(d));
	d[jx][jy] = 0;
	q.push(make_pair(jx, jy));
	int res = -1;
	while (!q.empty()) {
		int x = q.front().first, y = q.front().second; q.pop();
		int v = d[x][y];
		for (int k = 0; k < 4; ++ k) {
			int i = x + dx[k], j = y + dy[k];
			if (i < 0 || j < 0 || i >= n || j >= m || a[i][j] == '#' || d[i][j] != -1 || (f[i][j] != -1 && f[i][j] <= v + 1)) continue;
			d[i][j] = d[x][y] + 1;
			if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
				res = d[i][j];
				break;
			}
			q.push(make_pair(i, j));
		}
		if (res != -1) break;
	}
	if (res == -1) puts("IMPOSSIBLE");
	else printf("%d\n", res + 1);
}

int main() {
	scanf("%d%d", &n, &m);
	while (!q.empty()) q.pop();
	memset(f, -1, sizeof(f));
	for (int i = 0; i < n; ++ i) {
		scanf("%s", a[i]);
		for (int j = 0; j < m; ++ j) {
			if (a[i][j] == 'J') jx = i, jy = j;
			if (a[i][j] == 'F') {
				q.push(make_pair(i, j));
				f[i][j] = 0;
			}
		}
	}
	bfs();
	bfs2();
	return 0;
}

