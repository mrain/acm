#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
int n, m, tests, ans;
vector <int> e[30010], l[30010], c[30010];
typedef pair<int, int> PII;
vector <PII> res[30010];
bool vis[30010];

bool cmp(const PII &a, const PII &b) {
	return a.first < b.first || (a.first == b.first && a.second > b.second);
}

void dfs(int u) {
	vis[u] = true;
	res[u].push_back(make_pair(0, 0));
	for (int i = 0; i < (int)e[u].size(); ++ i) {
		int v = e[u][i], damage = c[u][i], len = l[u][i];
		if (vis[v]) continue;
		dfs(v);
		int k = (int)res[u].size() - 1;
		for (int j = 0; j < (int)res[v].size(); ++ j) {
			if (res[v][j].first + damage <= m)
				res[u].push_back(make_pair(res[v][j].first + damage, res[v][j].second + len));
			while (k >= 0 && res[v][j].first + damage + res[u][k].first > m) -- k;
			if (k == -1) continue;
			ans = max(ans, res[v][j].second + len + res[u][k].second);
		}
		res[v].clear();
		sort(res[u].begin(), res[u].end(), cmp);
		for (int i = 1; i < (int)res[u].size(); ++ i)
			res[u][i].second = max(res[u][i].second, res[u][i - 1].second);
		res[u].erase(unique(res[u].begin(), res[u].end()), res[u].end());
	}
}

int main() {
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++ i) {
			e[i].clear(); l[i].clear();
			c[i].clear(); res[i].clear();
		}
		for (int i = 0; i < n - 1; ++ i) {
			int a, b, C, D;
			scanf("%d%d%d%d", &a, &b, &C, &D);
			-- a, -- b;
			e[a].push_back(b);
			l[a].push_back(D);
			c[a].push_back(C);
			e[b].push_back(a);
			l[b].push_back(D);
			c[b].push_back(C);
		}
		memset(vis, 0, sizeof(vis));
		ans = 0;
		dfs(0);
		printf("Case %d: %d\n", ++ ca, ans);
	}
	return 0;
}

