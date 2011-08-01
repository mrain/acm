#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

vector<int> e[1010], w[1010];
int tests, n, m;
int deg[1010], dist[1010];
queue <int> q;

int main() {
	scanf("%d", &tests);
	while (tests --) {
		scanf("%d%d", &n, &m);
		memset(dist, 0, sizeof(dist));
		memset(deg, 0, sizeof(deg));
		while (!q.empty()) q.pop();
		int ans = 0;
		for (int i = 0; i < n; ++ i) e[i].clear(), w[i].clear();
		for (int i = 0; i < m; ++ i) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			e[a].push_back(b); w[a].push_back(c);
			++ deg[b];
		}
		for (int i = 0; i < n; ++ i)
			if (!deg[i]) q.push(i);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = 0; i < (int)e[u].size(); ++ i) {
				int v = e[u][i], c = w[u][i];
				-- deg[v]; dist[v] = max(dist[v], dist[u] + c);
				if (!deg[v]) q.push(v);
			}
			ans = max(ans, dist[u]);
		}
		cout << ans + 1 << endl;
	}
	return 0;
}

