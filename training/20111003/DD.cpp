#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (1005)

bool vis[maxn][maxn];
int g[maxn], a[maxn], b[maxn];
char buf[10];
int n, m, k;
bool flag;

void dfs(int i, int j) {
	if (flag) return ;
	if (vis[i][j]) return ;

	vis[i][j] = true;
	
	//printf("%d %d\n", i, j);
	
	if (i > m || j > n) return ;
	
	bool A = a[i] > 0 && g[a[i]] == 1, B = b[j] > 0 && g[b[j]] == 0;
	
	if (A && B) {
		flag = true; return;
	}
	
	if (!A) {
		if (a[i] < 0) g[-a[i]] = -1; else g[a[i]] = 0;
		dfs(i + 1, j); if (flag) return ;
		if (a[i] < 0) g[-a[i]] = 0; else g[a[i]] = -1;	
	}
	
	if (!B) {
		if (b[j] < 0) g[-b[j]] = -1; else g[b[j]] = 1;
		dfs(i, j + 1); if (flag) return;
		if (b[j] < 0) g[-b[j]] = 1; else g[b[j]] = -1;
	}
}

int main() {
	int T; scanf("%d", &T);
	
	while (T--) {
		memset(vis, 0, sizeof(vis));
		scanf("%d%d%d", &m, &n, &k);
		memset(g, -1, sizeof(g)); flag = false;
		
		for (int i = 1; i <= m; ++i) {
			int x; scanf("%s%d", buf, &x);
			a[i] = buf[0] == '+' ? x : -x;		
		}
		
		for (int i = 1; i <= n; ++i) {
			int x; scanf("%s%d", buf, &x);
			b[i] = buf[0] == '+' ? x : -x;		
		}
		
		dfs(1, 1);
		
		if (flag) puts(":-(");
		else puts(":-)");
	}

	return 0;
}
