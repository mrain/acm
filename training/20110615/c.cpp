#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {-1, 0, 1, 0};
const int n = 7, m = 7;
bool occ[10][10], den[10][10];
int sx[10000], sy[10000], Dx[10000], Dy[10000];
int x, y, tests, cnt;
int p;

inline bool avail(int a, int b) {
	return (a >= 0) && (b >= 0) && (a < n) && (b < n);
}

inline bool ispeg(int a, int b) {
	return avail(a, b) && occ[a][b];
}

inline bool can(int a, int b) {
	if (!avail(a, b)) return false;
	return !occ[a][b] && !den[a][b];
}

bool dfs(int d) {
	if (cnt == 1) {
		if (x > -1 && !occ[x][y]) return false;
		for (int i = 0; i < d; ++ i)
			printf("%d. (%d, %d) to (%d, %d)\n", i + 1, sy[i] + 1, sx[i] + 1, Dy[i] + 1, Dx[i] + 1);
		return true;
	}
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j)
			if (ispeg(i, j))
				for (int k = 0; k < 4; ++ k) {
					int mx = i + dx[k], my = j + dy[k];
					if (!ispeg(mx, my)) continue;
					if (!can(mx + dx[k], my + dy[k])) continue;
					occ[mx][my] = false;
					occ[i][j] = false;
					occ[mx + dx[k]][my + dy[k]] = true;
					-- cnt; sx[d] = i; sy[d] = j;
					Dx[d] = mx + dx[k]; Dy[d] = my + dy[k];
					if (dfs(d + 1)) return true;
					occ[mx][my] = true;
					occ[i][j] = true;
					occ[mx + dx[k]][my + dy[k]] = false;
					++ cnt;
				}
	return false;
}

int main() {
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		if (ca) puts("");
		memset(occ, 0, sizeof(occ));
		memset(den, 0, sizeof(den));
		x = y = -1; cnt = 0;
		bool flag = true;
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < n; ++ j) {
				char s[5];
				scanf("%s", s);
				if (isupper(s[0])) {
					if (x != -1) flag = false;
					x = i, y = j;
				}
				s[0] = tolower(s[0]);
				if (s[0] == 'x') den[i][j] = true;
				if (s[0] == 'o') occ[i][j] = true, ++ cnt;
			}
		printf("Dataset %d:\n", ++ ca);
		if (!flag || !dfs(0)) puts("No solution.");
	}
	return 0;
}

