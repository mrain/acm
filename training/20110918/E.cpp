#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define maxn (1100)
#define maxm (210)
#define PB push_back

vector<int> e[maxn], price[maxn], power[maxn];
int f[maxn][maxm];
bool vis[maxn];
int n, m;

inline int max(int x, int y) {
	return x > y ? x : y;
}

inline int min(int x, int y) {
	return x < y ? x : y;
}

void dfs(int x) {
	vis[x] = true;
	int cnt = 0;
	
	for (int i = 0; i < e[x].size(); ++i) {
		int k = e[x][i]; if (vis[k]) continue;
		dfs(k); 
				
		if (!cnt++) {
//			for (int a = 0; a <= m; ++a) //f[x][a] = max(f[x][a], f[k][a]);
//				if (f[k][a]) f[x][a]
			memcpy(f[x], f[k], (m + 1) * sizeof(int));
			
			continue;
		}
		
		for (int a = m; a >= 0; --a) {
//			for (int b = 0; b <= a; ++b)
	//			f[x][a] = max(f[x][a], min(f[x][a - b], f[k][b]));
			
			register int opt = 0;
			for (int b = 0; b <= a; ++b) {
				//opt = max(opt, min(f[x][a - b], f[k][b]));
				register int tmp = f[x][a - b];
				if (tmp > f[k][b]) tmp = f[k][b];
				if (opt < tmp) opt = tmp;
			}
			f[x][a] = opt;
			
		}
	}
	for (int j = m; j >= 0; --j) {
		register int org = f[x][j], X = 0;
		
		for (int i = 0; i < price[x].size(); ++i) if (j >= price[x][i]) {
			if (price[x][i] == 0) {
				X = max(X, power[x][i]);
				continue;
			}
			
			f[x][j] = max(f[x][j], f[x][j - price[x][i]] + power[x][i]);
		}	
		
		f[x][j] = max(f[x][j], org + X);
	}
}

void work() {

	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) e[i].clear();
	for (int i = 1; i < n; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		e[x].PB(y), e[y].PB(x);
	}
	
	scanf("%d", &m);
	for (int i = 1; i <= n; ++i) {
		int sum; scanf("%d", &sum);
		price[i].clear(), power[i].clear();
		
		for (int j = 0; j < sum; ++j) {
			int a, b; scanf("%d%d", &a, &b);
			price[i].PB(a), power[i].PB(b);
		} 
	}
	
	
	memset(f, 0, sizeof(f));
	memset(vis, 0, sizeof(vis));
	dfs(1);
	
	printf("%d\n", f[1][m]);
}

int main() {
	int T; scanf("%d", &T);
	
	while (T--) work();

	return 0;
}
