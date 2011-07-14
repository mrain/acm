#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int tests, n, m, k;
int to[20000], pre[20000], flow[20000], cost[20000], head[200];
int totalflow, totalcost, total, source, sink;
int dist[200];
bool used[200];
queue <int> q;

void addedge(int a, int b, int c, int w) {
	to[total] = b, flow[total] = c, cost[total] = w, pre[total] = head[a], head[a] = total ++;
	to[total] = a, flow[total] = 0, cost[total] = -w, pre[total] = head[b], head[b] = total ++;
}

bool SPFA() {
	while (!q.empty()) q.pop();
	memset(dist, 0x3F, sizeof(dist));
	memset(used, 0, sizeof(used));
	dist[source] = 0; used[source] = true;
	q.push(source);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int p = head[u]; p; p = pre[p]) {
			int v = to[p];
			if (dist[v] <= dist[u] + cost[p] || !flow[p]) continue;
			dist[v] = dist[u] + cost[p];
			if (!used[v]) q.push(v), used[v] = true;
		}
		used[u] = false;
	}
	if (dist[sink] == 0x3F3F3F3F) return false;
	return true;
}

int dfs(int u, int limit) {
	if (u == sink) return limit;
	used[u] = true;
	int now = 0;
	for (int p = head[u]; p; p = pre[p]) {
		int v = to[p];
		if (used[v] || dist[v] != dist[u] + cost[p] || !flow[p]) continue;
		int tmp = dfs(v, min(limit - now, flow[p]));
		now += tmp;
		flow[p] -= tmp;
		flow[p ^ 1] += tmp;
	}
	return now;
}

int main() {
	scanf("%d", &tests);
	while (tests --) {
		memset(head, 0, sizeof(head));
		memset(to, 0, sizeof(to));
		memset(flow, 0, sizeof(flow));
		memset(cost, 0, sizeof(cost));
		memset(pre, 0, sizeof(pre));
		totalflow = totalcost = 0; total = 2;
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 0; i < m; ++ i) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			addedge(a, b + n, 1, c);
		}
		source = 2 * n, sink = 2 * n + 1;
		for (int i = 0; i < n; ++ i) {
			addedge(source, i, k, 0);
			addedge(i + n, sink, k, 0);
		}
		while (SPFA()) {
			memset(used, 0, sizeof(used));
			int tmp = dfs(source, 2147483647);
			totalflow += tmp;
			totalcost += tmp * dist[sink];
		}
		if (totalflow != n * k) puts("-1");
		else printf("%d\n", totalcost);
	}
	return 0;
}

