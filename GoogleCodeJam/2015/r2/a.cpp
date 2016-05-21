#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

int tests, n, m;
string g[110];

bool chk(int x, int y, int dx, int dy) {
	x += dx; y += dy;
	while (x >= 0 && y >= 0 && x < n && y < m) {
		if (g[x][y] != '.') return true;
		x += dx; y += dy;
	}
	return false;
}

int main() {
	cin >> tests;
	for (int T = 1; T <= tests; ++ T) {
		cin >> n >> m;
		for (int i = 0; i < n; ++ i)
			cin >> g[i];

		int ans = 0;
		bool impossible = false;
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < m; ++ j) {
				if (g[i][j] == '.') continue;
				if (!chk(i, j, 1, 0) && !chk(i, j, 0, 1) && !chk(i, j, -1, 0) && !chk(i, j, 0, -1)) {
					impossible = true;
					break;
				}
				if (g[i][j] == '<' && !chk(i, j, 0, -1)) ++ ans;
				if (g[i][j] == '>' && !chk(i, j, 0, 1)) ++ ans;
				if (g[i][j] == 'v' && !chk(i, j, 1, 0)) ++ ans;
				if (g[i][j] == '^' && !chk(i, j, -1, 0)) ++ ans;
			}
			if (impossible) break;
		}
		if (impossible) printf("Case #%d: IMPOSSIBLE\n", T);
		else printf("Case #%d: %d\n", T, ans);
	}
    return 0;
}
