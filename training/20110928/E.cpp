#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

#define maxn (400)
#define PB push_back

struct edge {
	int to, cap, next;
	
	edge() {}
	edge(int a, int b, int c) : to(a), cap(b), next(c) {}
};

vector<edge> E;
int G[maxn];
int n, m, S, T;
int dis[maxn], vh[maxn];

const int inf = 10000;

int aug(int u, int tot) {
	//printf("%d %d\n", u, dis[u]);

	if (u == T) return tot;
	
	int his = tot, minh = n;
	
	for (int i = G[u]; i != -1; i = E[i].next) {
		if (E[i].cap == 0) continue;
		int v = E[i].to;
		//cout << u << ' ' << i << ' ' << E[i].cap << ' ' << v << ' ' << dis[v] << ' ' << dis[u] << endl;
		
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

void addEdge(int a, int b) {
	int tot = (int) E.size();
	E.PB(edge(b, 1, G[a])); G[a] = tot;
	E.PB(edge(a, 1, G[b])); G[b] = tot + 1;
}

int main() {
	scanf("%d%d", &n, &m);
	memset(G, -1, sizeof(G));
	for (int i = 0; i < m; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		addEdge(x, y);	
	}
	scanf("%d%d", &S, &T);
	
	vh[0] = n; int ans = 0;
	while (dis[S] <= n) ans += aug(S, inf);

	printf("%d\n", ans);
	
	int cnt = 0;
	for (int i = 0; i < E.size(); i += 2) {
		if (E[i].cap >= 1 && E[i ^ 1].cap == 0) cnt++;
//		cout << ' ' << i << ' ' << E[i].to << ' ' << E[i].cap << endl;
	}
		
	printf("%d\n", cnt);
	for (int i = 0; i < E.size(); i += 2) 
		if (E[i].cap >= 1 && E[i ^ 1].cap == 0) printf("%d\n", i / 2 + 1);
	
	return 0;
}
