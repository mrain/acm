#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

int dfn[20003], low[20003];
bool vis[20003];
vector <int> e[20003];
int n, m, ans, times;

int dfs(int father, int u) {
	low[u] = dfn[u] = ++ times;
	int cnt = 0;
	for (int i = 0; i < (int)e[u].size(); ++ i) {
		int v = e[u][i];
		if (v == father) continue;
		if (dfn[v]) {
			low[u] = min(low[u], dfn[v]);
			continue;
		}
		low[u] = min(low[u], dfs(u, v));
		if (low[v] >= dfn[u]) ++ cnt;
	}
	if (father != -1) cnt += 1;
	ans = max(ans, cnt);
	return low[u];
}

int main() {
	while (scanf("%d%d", &n, &m), (n || m)) {
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		for (int i = 0; i < n; ++ i) e[i].clear();
		for (int i = 0; i < m; ++ i) {
			int a, b;
			scanf("%d%d", &a, &b);
			e[a].push_back(b);
			e[b].push_back(a);
		}
		int cnt = 0; times = 0; ans = 0;
		for (int i = 0; i < n; ++ i)
			if (!dfn[i]) {
				dfs(-1, i);
				++ cnt;
			}
		cout << cnt + ans - 1 << endl;
	}
	return 0;
}
