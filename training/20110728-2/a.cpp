#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

bool g[500][500];
int n, tests, a[500], p[500], r[500];
int match[500], ans[500];
bool vis[500];

bool cmp(int x, int y) {
	return a[x] > a[y];
}

bool dfs(int u) {
	for (int v = 1; v <= n; ++ v) {
		if (!g[u][v] || vis[v]) continue;
		vis[v] = true;
		if (!match[v] || dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

int main() {
	scanf("%d", &tests);
	while (tests --) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++ i) scanf("%d", &a[i]), r[i] = i;
		sort(r + 1, r + n + 1, cmp);
		for (int i = 1; i <= n; ++ i) p[r[i]] = i;
		memset(g, 0, sizeof(g));
		for (int i = 1; i <= n; ++ i) {
			int k, tmp;
			scanf("%d", &k);
			for (int j = 0; j < k; ++ j) {
				scanf("%d", &tmp);
				g[p[i]][tmp] = true;
			}
		}
		memset(match, 0, sizeof(match));
		for (int i = 1; i <= n; ++ i) {
			memset(vis, 0, sizeof(vis));
			dfs(i);
		}
		memset(ans, 0, sizeof(ans));
		for (int i = 1; i <= n; ++ i)
			if (match[i]) ans[r[match[i]]] = i;
		for (int i = 1; i < n; ++ i) printf("%d ", ans[i]);
		printf("%d\n", ans[n]);
	}
	return 0;
}

