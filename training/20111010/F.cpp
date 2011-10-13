#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define maxn (20)

struct edge {
	int cap, to, next;
	
	edge() {}
	edge(int a, int b, int c) : cap(b), to(a), next(c) {}
} ;

int S, T, n, m;
int G[maxn], dis[maxn], vh[maxn];
vector<edge> E;

void addEdge(int a, int b, int c) {
	int tot = E.size();
	E.push_back(edge(b, c, G[a])); G[a] = tot;
	E.push_back(edge(a, 0, G[b])); G[b] = tot + 1;
}

int aug(int u, int tot) {
	if (u == T) return tot;
	
	int his = tot, minh = n;
	
	for (int i = G[u]; i != -1; i = E[i].next) {
		if (E[i].cap == 0) continue;
		int v = E[i].to;
		
		if (dis[v] + 1 == dis[u]) {
			int tmp = min(tot, E[i].cap);
			tmp = aug(v, tmp);
			E[i].cap -= tmp, E[i ^ 1].cap += tmp, tot -= tmp;
			
			if (dis[S] > n) return his - tot;
			if (tot == 0) break;
		}
		
		minh = min(minh, dis[v]);
	}
	
	if (his == tot) {
		--vh[dis[u]];
		
		if (vh[dis[u]] == 0) dis[S] = n + 1;
		
		dis[u] = minh + 1;
		++vh[dis[u]]; 
	}
	
	return his - tot;
}

int main() {
	int cases; scanf("%d", &cases);
	
	for (int t = 1; t <= cases; ++t) {
		printf("Case %d: ", t);
		
		scanf("%d%d", &n, &m); S = 1, T = n;
		memset(G, -1, sizeof(G));
		for (int i = 0; i < m; ++i) {
			int a, b, c; scanf("%d%d%d", &a, &b, &c);
			addEdge(a, b, c);
		}
		
		memset(dis, 0, sizeof(dis));
		memset(vh, 0, sizeof(vh)); vh[0] = n;
		
		int ans = 0;
		while (dis[S] <= n) ans += aug(S, 100000000);
		
		printf("%d\n", ans);
	}

	return 0;
}
