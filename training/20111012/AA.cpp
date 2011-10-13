#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define maxn (30)

double x[maxn], y[maxn];
double d[maxn][maxn];
double f[(1 << 20) + 5];/*
vector<int> g[(1 << 20) + 5];*/
bool vis[maxn];
int n;

int main() {
/*
	for (int i = 0; i < 1 << 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			if (i & (1 << j)) continue;
			
			g[i].push_back(j + 1);
		}
	}
*/
	int T; T = 100;
	
	for (int t = 1; t <= T; ++t) {
		printf("Case #%d: ", t);
		
		n = 20;
		for (int i = 1; i <= n; ++i) x[i] = (double) (rand() % 2000 - 1000), y[i] = (double) (rand() % 2000 - 1000);
		
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= n; ++j)
				d[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
				
		memset(vis, 0, sizeof(vis)); double opt = 0.;
 		for (int i = 1; i <= n / 2; ++i) {
 			int x = -1;
 			for (int j = 1; j <= n; ++j) if (!vis[j] && (x == -1 || d[0][x] > d[0][j])) x = j;
 			opt += d[0][x], vis[x] = true;
 			
 			int y = -1;
 			for (int j = 1; j <= n; ++j) if (!vis[j] && (y == -1 || d[x][y] > d[x][j])) y = j;
 			opt += d[x][y], vis[y] = true;
 		}
				
		for (int k = 0; k < (1 << n); ++k) f[k] = 1e200;
		f[0] = 0.;
		
		for (int k = 0; k < (1 << n); ++k) {
			if (f[k] > opt) continue; 
			
			for (int i = 0; i < n; ++i) {
				if (k & (1 << i)) continue;
				
				for (int j = i + 1; j < n; ++j) {
					if (k & (1 << j)) continue;
					
					int to = k + (1 << i) + (1 << j);
					f[to] = min(f[to], f[k] + min(d[0][i + 1] + d[i + 1][j + 1], d[0][j + 1] + d[j + 1][i + 1]));
				}
				
				break;
			}

/*
			if (((int) g[k].size()) & 1) continue;
			
			int i = g[k][0];
			for (int p = 1; p < g[k].size(); ++p) {
				int j = g[k][p];
				
				int to = k + (((1 << i) + (1 << j)) >> 1);
				f[to] = min(f[to], f[k] + min(d[0][i], d[0][j]) + d[i][j]);
			}
*/
		}
		
		printf("%.2f\n", min(opt, f[(1 << n) - 1]));
	}

	return 0;
}
