#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (300)
#define A first
#define B second
#define MP make_pair

typedef pair<int, int> PII;

const int inf = 4000000;
int s[maxn];
int f[2][maxn][maxn];
int r[2][maxn][maxn];
PII g[maxn];
int n;

void dfs(int k, int i, int j) {
	int x = r[k][i][j]; if (x == -1) return ;
	if (x == 0) {
		dfs(0, i - 1, j); printf("%d ", i - 1);
	}
	if (x == 1) {
		dfs(1, i, j + 1); printf("%d ", j + 1);
	}
}

void work() {
	for (int i = 1; i <= n; ++i) scanf("%d", &g[i].B);
	for (int i = 1; i <= n; ++i) scanf("%d", &g[i].A);
	sort(g + 1, g + 1 + n);

	memset(f, 0, sizeof(f)); memset(r, -1, sizeof(r));
	f[0][1][n] = max(g[1].B, g[n].B - g[n].A + g[1].A), f[1][1][n] = max(g[n].B, g[1].B - g[n].A + g[1].A);
	
	for (int k = n - 1; k > 0; --k)
		for (int i = 1; i + k <= n; ++i) {
			int j = i + k;
			if (f[0][i][j] > 0) {
				int tmp = min(f[0][i][j] - g[i + 1].A + g[i].A, g[i].B);
				if (tmp > f[0][i + 1][j]) f[0][i + 1][j] = tmp, r[0][i + 1][j] = 0;
				tmp -= g[j].A - g[i + 1].A;
				if (tmp > f[1][i + 1][j]) f[1][i + 1][j] = tmp, r[1][i + 1][j] = 0;
				
				//printf("%d %d %d = %d\n", 0, i, j, f[0][i][j]);
			}
			if (f[1][i][j] > 0) {
				int tmp = min(f[1][i][j] - g[j].A + g[j - 1].A, g[j].B);
				if (tmp > f[1][i][j - 1]) f[1][i][j - 1] = tmp, r[1][i][j - 1] = 1;
				tmp -= g[j - 1].A - g[i].A;
				if (tmp > f[0][i][j - 1]) f[0][i][j - 1] = tmp, r[0][i][j - 1] = 1;
				//printf("%d %d %d = %d\n", 1, i, j, f[1][i][j]);
			}
		}
		
	for (int i = 1; i <= n; ++i) {
		if (f[0][i][i]) {
			dfs(0, i, i); printf("%d\n", i); return ;
		}
		if (f[1][i][i]) {
			dfs(1, i, i); printf("%d\n", i); return ;
		}
	}
	
	puts("Mission Impossible");
}

int main() {
	while (scanf("%d", &n) == 1) work();

	return 0;
}
