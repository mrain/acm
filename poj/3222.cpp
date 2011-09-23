#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int n, m;
vector <int> be[20010], ra, rb, rc;
int head[20010], to[200010], next[200010], tot;
bool vis[20010], block[200010], use[20010];

inline void addedge(int u, int v) {
	to[tot] = v; next[tot] = head[u]; head[u] = tot ++;
}

int dfs(int u) {
	int ret = 0;
	vis[u] = true;
	for (int i = head[u]; i; i = next[i]) {
		if (block[i]) continue;
		block[i ^ 1] = true;
		int v = to[i];
		if (vis[v]) {
			be[u].push_back(v);
			continue;
		}
		ret += dfs(v);
	}
	return ret + be[u].size() + 1;
}

void solve(int u, int fa) {
	vis[u] = true;
	for (int i = head[u]; i; i = next[i]) {
		int v = to[i];
		if (block[i] || vis[v]) continue;
		solve(v, u);
		if (!use[v]) be[u].push_back(v);
	}
	for (int i = 0; 2 * i + 1 < (int)be[u].size(); ++ i)
		printf("%d %d %d\n", be[u][2 * i], u, be[u][2 * i + 1]);
	if (((int)be[u].size() & 1) == 1) {
		printf("%d %d %d\n", be[u][be[u].size() - 1], u, fa);
		use[u] = true;
	}
}

int main() {
	scanf("%d%d", &n, &m); tot = 2;
	for (int i = 0; i < m; ++ i) {
		int a, b;
		scanf("%d%d", &a, &b);
		addedge(a, b); addedge(b, a);
	}
	for (int i = 1; i <= n; ++ i)
		if (!vis[i]) {
			if ((dfs(i) & 1) == 0) {
				puts("NO");
				return 0;
			}
		}
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; ++ i)
		if (!vis[i]) solve(i, 0);
	return 0;
}

