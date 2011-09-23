#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int f[110][110];
bool d[110][110];
int n, tests;

int main() {
	scanf("%d", &tests);
	int cas = 0;
	while (tests --) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < n; ++ j)
				scanf("%d", &f[i][j]);
		int ans = 0;
		memset(d, 0, sizeof(d));
		for (int k = 0; k < n; ++ k)
			for (int i = 0; i < n; ++ i)
				for (int j = 0; j < n; ++ j) {
					if (i == j || j == k || i == k) continue;
					if (f[i][j] > f[i][k] + f[k][j])
						goto IMPOSSIBLE;
					else if (f[i][j] == f[i][k] + f[k][j])
						d[i][j] = true;
				}
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < n; ++ j)
				if (i != j && !d[i][j]) ++ ans;
		printf("Case %d: %d\n", ++ cas, ans);
		continue;

IMPOSSIBLE:
		printf("Case %d: impossible\n", ++ cas);
	}
	return 0;
}

