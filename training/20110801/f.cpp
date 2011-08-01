#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

const int inf = 2147483647;
int to[200010], w[200010], f[200010], head[200010], next[200010];
int dist[200010];
int tests, n, m, k, edgecnt, source, sink;
bool vis[200010];
queue <int> q;

void addedge(int a, int b, int flow, int cost) {
	//printf("%d->%d: %d %d\n", a, b, flow, cost);
	to[edgecnt] = b; w[edgecnt] = cost; f[edgecnt] = flow;
	next[edgecnt] = head[a]; head[a] = edgecnt ++;
	to[edgecnt] = a; w[edgecnt] = -cost; f[edgecnt] = 0;
	next[edgecnt] = head[b]; head[b] = edgecnt ++;
}

bool spfa() {
	static bool inq[200010];
	memset(inq, 0, sizeof(inq));
	memset(dist, 0xFF, sizeof(dist));
	while (!q.empty()) q.pop();
	inq[source] = true; q.push(source);
	dist[source] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = head[u]; i; i = next[i]) {
			if (!f[i]) continue;
			int v = to[i], cost = w[i];
			if (dist[v] < dist[u] + cost) {
				dist[v] = dist[u] + cost;
				if (!inq[v]) inq[v] = true, q.push(v);
			}
		}
		inq[u] = false;
	}
	return dist[sink] != -1;
}

int dfs(int u, int flow) {
	int now = 0;
	if (u == sink) return flow;
	if (flow == 0) return 0;
	vis[u] = true;
	for (int i = head[u]; i; i = next[i]) {
		int v = to[i];
		if (vis[v] || !f[i]) continue;
		if (dist[v] == dist[u] + w[i]) {
			int tmp = dfs(v, min(flow - now, f[i]));
			now += tmp;
			f[i] -= tmp; f[i ^ 1] += tmp;
			if (flow == now) break;
		}
	}
	return now;
}

int main() {
	scanf("%d", &tests);
	while (tests --) {
		memset(head, 0, sizeof(head));
		memset(next, 0, sizeof(next));
		edgecnt = 2;
		scanf("%d%d%d", &n, &m, &k);
		source = n; sink = n + 1;
		addedge(source, 0, k, 0);
		for (int i = 0; i < n; ++ i) {
			int tmp;
			scanf("%d", &tmp);
			if (i == n - 1) addedge(i, sink, inf, 0);
			else addedge(i, i + 1, inf, 0);
			if (i + m < n) addedge(i, i + m, 1, tmp);
			else addedge(i, sink, 1, tmp);
		}
		int ans = 0;
		while (spfa()) {
			memset(vis, 0, sizeof(vis));
			int det = dfs(source, inf);
			ans += det * dist[sink];
		}
		cout << ans << endl;
	}
	return 0;
}

