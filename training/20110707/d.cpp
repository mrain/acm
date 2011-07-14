#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;

int f[1010][1010][2], g[1010][1010];
char a[1010], b[1010];
int n, m, k;

int main() {
	while (1) {
		gets(a);
		sscanf(a, "%d", &k);
		if (k == 0) break;
//		memset(f, 0, sizeof(f));
//		memset(g, 0, sizeof(g));
		gets(a + 1); gets(b + 1);
		n = strlen(a + 1), m = strlen(b + 1);
		for (int i = 0; i <= n; ++ i)
			for (int j = 0; j <= m; ++ j) {
				f[i][j][0] = 0;
				f[i][j][1] = -1;
			}
		for (int i = 1; i <= n; ++ i)
			for (int j = 1; j <= m; ++ j) {
				if (a[i] == b[j]) g[i][j] = g[i - 1][j - 1] + 1;
				else g[i][j] = 0;
//				f[i][j] = max(f[i - 1][j], f[i][j - 1]);
				f[i][j][0] = max(
						max(f[i - 1][j][0], f[i][j - 1][0]),
						max(f[i - 1][j][1], f[i][j - 1][1])
						);
				if (a[i] == b[j]) {
					if (f[i - 1][j - 1][1] != -1)
						f[i][j][1] = f[i - 1][j - 1][1] + 1;
					if (g[i][j] >= k)
						f[i][j][1] = max(
								f[i][j][1],
								max(f[i - k][j - k][1], f[i - k][j - k][0]) + k
							);
				}
			}
		printf("%d\n", max(f[n][m][0], f[n][m][1]));
	}
	return 0;
}
