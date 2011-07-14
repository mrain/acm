#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;

int n, k, sh, sc;
int a[100010], b[100010], l[100010], x[100010], cnt[100010], chose[100010];
vector <int> e[100010], id[100010];
bool vis[100010];

void dfs(int u) {
	vis[u] = true; cnt[u] = 1;
	for (int i = 0; i < (int)e[u].size(); ++ i) {
		int v = e[u][i], p = id[u][i];
		if (vis[v]) continue;
		dfs(v);
		x[p] = (n - cnt[v]) * cnt[v];
		cnt[u] += cnt[v];
	}
}

bool cmp(const int a, const int b) {
	return (long long)x[a] * (long long)l[a] > (long long)x[b] * (long long)l[b];
}
bool cmp2(const int a, const int b) {
	return (long long)x[a] * (long long)l[a] < (long long)x[b] * (long long)l[b];
}

int main() {
	scanf("%d%d%d%d", &n, &k, &sh, &sc);
	for (int i = 1; i < n; ++ i) {
		scanf("%d%d%d", a + i, b + i, l + i);
		-- a[i]; -- b[i];
		e[a[i]].push_back(b[i]);
		e[b[i]].push_back(a[i]);
		id[a[i]].push_back(i);
		id[b[i]].push_back(i);
		chose[i] = i;
	}
	dfs(0);
	if (sh < sc) sort(chose + 1, chose + n, cmp);
	else sort(chose + 1, chose + n, cmp2);
	for (int i = 1; i < k + 1; ++ i)
		printf("%s%d", i == 1 ? "" : " ", chose[i]);
	puts("");
	return 0;
}

