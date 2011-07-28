#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int invalid = 0x3F3F3F3F;
int tests, n, m, s, t;
int ds[500], dt[500];
int a[160010], b[160010];
vector <int> e[500], ans;
queue <int> q;

void bfs(int s, int *d) {
	static bool vis[500];
	memset(vis, 0, sizeof(vis));
	memset(d, 0x3F, sizeof(int) * n);
	d[s] = 0; vis[s] = true;
	while (!q.empty()) q.pop();
	for (q.push(s); !q.empty();) {
		int u = q.front(); q.pop();
		for (int i = 0; i < (int)e[u].size(); ++ i) {
			int v = e[u][i];
			if (vis[v]) continue;
			vis[v] = true; d[v] = d[u] + 1;
			q.push(v);
		}
	}
}

void make(int d, vector <int> &res) {
	for (int i = 0; i < m; ++ i) {
		if (ds[a[i]] == invalid) continue;
		if (ds[a[i]] > ds[b[i]]) swap(a[i], b[i]);
		if (ds[a[i]] == d && dt[b[i]] != invalid)
			res.push_back(i);
	}
}

int main() {
	scanf("%d", &tests);
	while (tests --) {
		scanf("%d%d%d%d", &n, &m, &s, &t); -- s, -- t;
		for (int i = 0; i < n; ++ i) e[i].clear();
		for (int i = 0; i < m; ++ i) {
			scanf("%d%d", &a[i], &b[i]);
			-- a[i], -- b[i];
			e[a[i]].push_back(b[i]);
			e[b[i]].push_back(a[i]);
		}
		bfs(s, ds); bfs(t, dt);
		printf("%d\n", ds[t]);
		for (int i = 0; i < ds[t]; ++ i) {
			ans.clear();
			make(i, ans);
			sort(ans.begin(), ans.end());
			printf("%d", ans.size());
			for (int j = 0; j < (int)ans.size(); ++ j)
				printf(" %d", ans[j] + 1);
			puts("");
		}
	}
	return 0;
}

