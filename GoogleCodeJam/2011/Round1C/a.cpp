#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int tests, n, m;
char a[100][100], res[100][100];

inline bool valid(int x, int y) {
	return a[x][y] == '#' && a[x + 1][y] == '#' && a[x][y + 1] == '#' && a[x + 1][y + 1] == '#';
}

int main() {
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		printf("Case #%d:\n", ++ ca);
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++ i)
			scanf("%s", a[i]);
		bool avai = true;
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < m; ++ j)
				if (a[i][j] == '#') {
					if (!valid(i, j)) {
						avai = false;
						break;
					}
					a[i][j] = '/';
					a[i][j + 1] = '\\';
					a[i + 1][j] = '\\';
					a[i + 1][j + 1] = '/';
				}
			if (!avai) break;
		}
		if (!avai) {
			puts("Impossible");
		} else {
			for (int i = 0; i < n; ++ i)
				puts(a[i]);
		}
	}
	return 0;
}

