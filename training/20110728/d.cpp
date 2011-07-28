#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>
using namespace std;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
int n, m, a[50][50];
int s, r, b, l;
int d[50][50][4];
bool inq[50][50][4];
typedef pair<int, int> PII;
typedef pair<PII, int> PIII;
queue <PIII> q;

inline bool valid(int x, int y) {
	return x >= 0 && y >= 0 && x < n && y < m;
}

void update(int x, int y, int dir, int v) {
	if (d[x][y][dir] > v) {
		d[x][y][dir] = v;
		if (!inq[x][y][dir]) {
			q.push(make_pair(make_pair(x, y), dir));
			inq[x][y][dir] = true;
		}
	}
}

int main() {
	while (scanf("%d%d", &m, &n) == 2 && n + m) {
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < m; ++ j)
				scanf("%d", &a[i][j]);
		scanf("%d%d%d%d", &s, &r, &b, &l);
		memset(d, 0x3F, sizeof(d));
		memset(inq, 0, sizeof(inq));
		d[0][0][0] = 0; inq[0][0][0] = true;
		while (!q.empty()) q.pop();
		q.push(make_pair(make_pair(0, 0), 0));
		while (!q.empty()) {
			int x = q.front().first.first, y = q.front().first.second;
			int dir = q.front().second; q.pop();
			int v = d[x][y][dir];
			if (x == n && y == m) continue;
			int nx, ny, ndir;
			//straight;
			ndir = dir; nx = x + dx[ndir]; ny = y + dy[ndir];
			if (valid(nx, ny)) update(nx, ny, ndir, v + (a[x][y] == 0 ? 0 : s));
			//right;
			ndir = (dir + 1) % 4; nx = x + dx[ndir]; ny = y + dy[ndir];
			if (valid(nx, ny)) update(nx, ny, ndir, v + (a[x][y] == 1 ? 0 : r));
			//back;
			ndir = (dir + 2) % 4; nx = x + dx[ndir]; ny = y + dy[ndir];
			if (valid(nx, ny)) update(nx, ny, ndir, v + (a[x][y] == 2 ? 0 : b));
			//left;
			ndir = (dir + 3) % 4; nx = x + dx[ndir]; ny = y + dy[ndir];
			if (valid(nx, ny)) update(nx, ny, ndir, v + (a[x][y] == 3 ? 0 : l));
			inq[x][y][dir] = false;
		}
		int ans = 0x3F3F3F3F;
		for (int k = 0; k < 3; ++ k)
			ans = min(ans, d[n - 1][m - 1][k]);
		cout << ans << endl;
	}
	return 0;
}

