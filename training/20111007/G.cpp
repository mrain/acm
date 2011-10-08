#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define maxn (205)

struct edge{
	int to, v, nxt;
	bool flag;
	
	edge() : flag(false) {}
	edge(int a, int b, int c, bool d) : to(a), v(b), nxt(c), flag(d) {}
};

vector<edge> E;
int n, m, s, t, visCnt, turCnt, ans;
int pre[maxn], vis[maxn], tur[maxn], dis[maxn], G[maxn];
bool circle;

const int inf = 1000000000;

void addEdge(int a, int b, int c) {
	int tot = E.size();
	E.push_back(edge(b, c, G[a], true)); G[a] = tot;
	E.push_back(edge(a, -c, G[b], false)); G[b] = tot + 1;
}

void init() {
	E.clear();
	memset(G, -1, sizeof(G));

	scanf("%d%d%d%d", &n, &m, &s, &t);
	ans = 0;
	for (int i = 0; i < m; ++i) {
		int st, ed, a, b; scanf("%d%d%d%d", &st, &ed, &a, &b);
		
		addEdge(st, ed, a - b), ans += b;
	}
}

void dfs(int x) {
	vis[x] = true;
	
	for (int i = G[x]; i != -1; i = E[i].nxt) {
		if (!E[i].flag) continue;
		
		int k = E[i].to;
		if (vis[k]) continue;
		pre[k] = i; dfs(k);
	}
}

void firstRoute() {
	int k = t;
	
	while (k != s) {
	
		ans += E[pre[k]].v;
		//printf("R %d %d\n", ans, k);
		E[pre[k]].flag = false, E[pre[k] ^ 1].flag = true;
		k = E[pre[k] ^ 1].to;
	}
}

void Route(int x, int i, int from) {
	int k = x; circle = true;

	ans += E[i].v;
	E[i].flag = false, E[i ^ 1].flag = true;

	while (k != from) {
		dis[k] = inf, vis[k] = 0;
		
		ans += E[pre[k]].v;
		//printf("R %d %d\n", ans, k);
		E[pre[k]].flag = false, E[pre[k] ^ 1].flag = true;
		k = E[pre[k] ^ 1].to;
	}
}	

void spfa(int x) {
	vis[x] = visCnt, tur[x] = turCnt;
	
	//printf("S %d %d %d %d\n", x, dis[x], visCnt, ans);
	
	for (int i = G[x]; i != -1; i = E[i].nxt) {
		if (!E[i].flag || dis[x] >= inf) continue;
		
		int k = E[i].to, v = E[i].v;
		
		if (turCnt == tur[k] && visCnt != vis[k]) continue;
		
		if (dis[x] + v < dis[k]) {
			if (vis[k] != visCnt) {
				pre[k] = i, dis[k] = dis[x] + v; spfa(k);
			}
			else {
				Route(x, i, k); return ;
			}
		}
	}
	
	vis[x] = 0;
}

void work() {
	memset(vis, 0, sizeof(vis)), memset(pre, -1, sizeof(pre));
	dfs(s);
	if (!vis[t]) {
		puts("impossible"); return ;
	}
	
	firstRoute();
	
	circle = true, visCnt = turCnt = 0;
	memset(tur, 0, sizeof(tur)), memset(vis, 0, sizeof(vis));
	
	while (circle) {
		for (int i = 1; i <= n; ++i) dis[i] = inf, pre[i] = -1;
		
		circle = false, turCnt++;
		for (int i = 1; i <= n; ++i) {
			if (tur[i] == turCnt) continue;
			dis[i] = 0, visCnt++; spfa(i);
		}
	}
	
	printf("%d\n", ans);
}

int main() {
	int cases; scanf("%d", &cases);
	for (int i = 1; i <= cases; ++i) {
		printf("Case %d: ", i);
		init(); work();
	}

	return 0;
}
