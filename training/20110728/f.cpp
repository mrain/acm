#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <set>
#include <vector>
using namespace std;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
int n, m, cnt, det;
int a[15][15];
bool v[15][15];
int sx, sy, tx, ty;
int flip;
typedef set<int> shape;
set<shape> vis;
shape s;

inline bool valid(int x, int y) {
	return x >= 0 && y >= 0 && x < n && y < m && a[x][y];
}

void rotate(int x, int y, int &nx, int &ny, int det) {
	int dx = x - sx, dy = y - sy;
	dx *= flip;
	if (det == 0) nx = dx + tx, ny = dy + ty;
	else if (det == 1) nx = -dy + tx, ny = dx + ty;
	else if (det == 2) nx = -dx + tx, ny = -dy + ty;
	else if (det == 3) nx = dy + tx, ny = -dx + ty;
}

bool dfs() {
	if ((int)s.size() == cnt) return true;
	vector <int> list;
	for (shape::iterator it = s.begin(); it != s.end(); ++ it) {
//		list.push_back(*it);
//	}
//	for (int i = 0; i < (int)list.size(); ++ i) {
//		int x = list[i] / m, y = list[i] % m;
		int x = *it / m, y = *it % m;
		for (int k = 0; k < 4; ++ k) {
			int nx = x + dx[k], ny = y + dy[k];
			if (!valid(nx, ny) || v[nx][ny]) continue;
			int fx, fy;
			rotate(nx, ny, fx, fy, det);
			if (nx == fx && ny == fy) continue;
			if (!valid(fx, fy) || v[fx][fy]) continue;
			s.insert(nx * m + ny);
			if (!vis.count(s)) {
				vis.insert(s);
				v[fx][fy] = v[nx][ny] = true;
				if (dfs()) return true;
				v[fx][fy] = v[nx][ny] = false;
			}
			s.erase(s.find(nx * m + ny));
		}
	}
	return false;
}

bool good() {
	for (det = 0; det < 4; ++ det) {
		vis.clear();
		memset(v, 0, sizeof(v));
		s.clear();
		s.insert(sx * m + sy);
		v[tx][ty] = v[sx][sy] = true;
		vis.insert(s);
		if (dfs()) return true;
	}
	return false;
}

bool check() {
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < m; ++ j)
			if (a[i][j]) {
				sx = i, sy = j;
				break;
			}
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < m; ++ j)
			if (a[i][j] && (i != sx || j != sy)) {
				tx = i, ty = j;
				flip = 1;
				if (good()) return true;
				flip = -1;
				if (good()) return true;
			
	return false;
}

int main() {
	while (scanf("%d%d", &m, &n) == 2 && n + m) {
		cnt = 0;
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < m; ++ j)
				scanf("%d", &a[i][j]), cnt += a[i][j];
		if (cnt < 2 || (cnt & 1)) {
			puts("NO");
			continue;
		}
		cnt >>= 1;
		puts(check() ? "YES" : "NO");
	}
	return 0;
}

