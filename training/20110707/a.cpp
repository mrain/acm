#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

vector <int> to[600], w[600], to2[6000], w2[6000];
int n, m, s, t, dist[6000], res[6000], dist2[6000];
queue <int> q;
bool inq[6000];

void sssp() {
	memset(inq, 0, sizeof(inq));
	while (!q.empty()) q.pop();
	q.push(s); inq[s] = true;
	memset(dist, 0x1F, sizeof(dist)); dist[s] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < (int)to[u].size(); ++ i) {
			int v = to[u][i];
			if (dist[v] > dist[u] + w[u][i]) {
				dist[v] = dist[u] + w[u][i];
				if (!inq[v]) q.push(v), inq[v] = true;
			}
		}
		inq[u] = false;
	}
}

void pullback() {
	memset(inq, 0, sizeof(inq));
	while (!q.empty()) q.pop();
	q.push(t); inq[t] = true;
	memset(dist2, 0x1F, sizeof(dist2)); dist2[t] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < (int)to2[u].size(); ++ i) {
			int v = to2[u][i];
			if (dist2[v] > dist2[u] + w2[u][i]) {
				dist2[v] = dist2[u] + w2[u][i];
				if (!inq[v]) q.push(v), inq[v] = true;
			}
		}
		inq[u] = false;
	}
}

void sssp2() {
	memset(inq, 0, sizeof(inq));
	while (!q.empty()) q.pop();
	q.push(s); inq[s] = true;
	memset(res, 0x1F, sizeof(res)); res[s] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < (int)to[u].size(); ++ i) {
			int v = to[u][i];
			if (dist[u] + dist2[v] + w[u][i] == dist[t]) continue;
			if (res[v] > res[u] + w[u][i]) {
				res[v] = res[u] + w[u][i];
				if (!inq[v]) q.push(v), inq[v] = true;
			}
		}
		inq[u] = false;
	}
}

int main() {
	while (1) {
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0) break;
		for (int i = 0; i < n; ++ i) to[i].clear(), w[i].clear();
		for (int i = 0; i < n; ++ i) to2[i].clear(), w2[i].clear();
		scanf("%d%d", &s, &t);
		for (int i = 0; i < m; ++ i) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			to[a].push_back(b);
			w[a].push_back(c);
			to2[b].push_back(a);
			w2[b].push_back(c);
		}
		sssp();
		pullback();
		sssp2();
		if (res[t] == 0x1F1F1F1F) res[t] = -1;
		printf("%d\n", res[t]);
	}
	return 0;
}
