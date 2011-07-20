#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int dx[9] = {0, 0, 0, -1, -1, 1, 1, -2, 2};
const int dy[9] = {1, 2, 3, 1, 2, 1, 2, 1, 1};

struct record {
	int x, y, k;
	record(int x = 0, int y = 0, int k = 0)
		: x(x), y(y), k(k) {}
};

queue<record> q;
int g[100][100], n, m;
int d[100][100][2];
bool inq[100][100][2];
char buf[30];

int bfs() {
	while (!q.empty()) {
		record tmp = q.front(); q.pop();
		int x = tmp.x, y = tmp.y, k = tmp.k, xs = (k == 0 ? -1 : 1), c = d[x][y][k];
		for (int i = 0; i < 9; ++ i) {
			int nx = x + dx[i], ny = y + xs * dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m || g[nx][ny] == -1) continue;
			if (d[nx][ny][k ^ 1] > c + g[nx][ny]) {
				d[nx][ny][k ^ 1] = c + g[nx][ny];
				if (!inq[nx][ny][k ^ 1])
					q.push(record(nx, ny, k ^ 1)), inq[nx][ny][k ^ 1] = true;
			}
		}
		inq[x][y][k] = false;
	}
/*	
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < m; ++ j)
			cout << d[i][j][0] << ' ';
		cout << endl;
	}
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < m; ++ j)
			cout << d[i][j][1] << ' ';
		cout << endl;
	}*/
	int ret = 0x1F1F1F1F;
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < m; ++ j)
			for (int k = 0; k < 2; ++ k)
				if (g[i][j] == 0)
					ret = min(ret, d[i][j][k]);
	if (ret == 0x1F1F1F1F) ret = -1;
	return ret;
}

int main() {
	while (scanf("%d%d", &m, &n) == 2 && (n || m)) {
		memset(d, 0x1F, sizeof(d));
		memset(inq, 0, sizeof(inq));
		while (!q.empty()) q.pop();
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < m; ++ j) {
				scanf("%s", buf);
				if (!isdigit(buf[0])) g[i][j] = -1;
				else g[i][j] = buf[0] - '0';
				if (buf[0] == 'T') g[i][j] = 0;
				if (buf[0] == 'S') {
					q.push(record(i, j, 0));
					q.push(record(i, j, 1));
					d[i][j][0] = d[i][j][1] = 0;
					inq[i][j][0] = inq[i][j][1] = 1;
				}
			}
		printf("%d\n", bfs());
	}
	return 0;
}

