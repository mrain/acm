#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define maxn (5000)
#define maxm (5000000)

struct edge{
	int to, cap, nxt;
	
	edge() {}
	edge(int a, int b, int c) : to(a), cap(b), nxt(c) {}
} E[maxm];

int G[maxn];
int edges, m, n, ans, S, T;
string a, b;
int cnt[2][maxn];
int dis[maxn], vh[maxn];
bool vis1[maxn], vis2[maxn];

const int inf = (~0u>>1);

void addEdge(int a, int b, int c) {
	//printf("%d -> %d : %d\n", a, b, c);

	E[edges] = edge(b, c, G[a]);
	G[a] = edges++;
	E[edges] = edge(a, 0, G[b]);
	G[b] = edges++;
}

int aug(int u, int tot) {
	if (u == T) return tot;
	
	int his = tot, minh = T;
	
	for (int i = G[u]; i != -1; i = E[i].nxt) {
		if (E[i].cap == 0) continue;
		int v = E[i].to;
		if (dis[v] + 1 == dis[u]) {
			int tmp = min(tot, E[i].cap);
			tmp = aug(v, tmp);
			E[i].cap -= tmp, E[i ^ 1].cap += tmp, tot -= tmp;
			
			if (dis[S] > T) return his - tot;
			if (tot == 0) break;
		} 
		minh = min(minh, dis[v]);
	}
	
	if (his == tot) {
		--vh[dis[u]];
		
		if (vh[dis[u]] == 0) dis[S] = T + 1;
		
		dis[u] = minh + 1;
		++vh[dis[u]];
	}
	
	return his - tot;
}

void init() {
	S = 0, T = m + n + m + n + 1;
	memset(G, -1, sizeof(G));

	for (int i = 0; i <= m - n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (a[i + j] == '?') {
				if (b[j] == '?') addEdge(i + j + 1, m + n + m + j + 1, 1), addEdge(m + j + 1, m + n + i + j + 1, 1);
				else cnt[b[j] - '0'][i + j + 1]++;
			}
			else {
				if (b[j] == '?') cnt[a[i + j] - '0'][m + j + 1]++;
				else {
					if (a[i + j] != b[j]) ans++;
				}
			} 
		} 
	}
	
	for (int i = 1; i <= m + n; ++i) {
		if (cnt[0][i]) addEdge(m + n + i, T, cnt[0][i]);
		if (cnt[1][i]) addEdge(S, i, cnt[1][i]);
	}
	
	for (int i = 1; i <= m + n; ++i)
		addEdge(i, m + n + i, inf);
}

int main() {
	cin >> a >> b; 
	m = (int) a.length(), n = (int) b.length();
	
	init();
	
	while (dis[S] <= T) ans += aug(S, inf);
	
	a += b;
/*
	for (int i = G[S]; i != -1; i = E[i].nxt) 
		if (a[E[i].to - 1] == '?') {
			if (E[i].cap) a[E[i].to - 1] = '1'; else a[E[i].to - 1] = '0';
		}
	for (int i = G[T]; i != -1; i = E[i].nxt)
		if (a[E[i].to - m - n - 1] == '?') {
			if (E[i ^ 1].cap) a[E[i].to - m - n - 1] = '0';
			else a[E[i].to - m - n - 1] = '1';
		}		
*/		
	
	queue<int> q; 
	while (!q.empty()) q.pop();
	q.push(S), vis1[S] = true;
	while (!q.empty()) {
		int k = q.front(); q.pop();
		
		for (int i = G[k]; i != -1; i = E[i].nxt) {
			int x = E[i].to;
			if (vis1[x] || !E[i].cap) continue;
//			cout << x << endl;
			vis1[x] = true, q.push(x);
			
			if (x <= m + n) a[x - 1] = '0';
			else a[x - m - n - 1] = '1'; 
		}
	}
	
	//memset(vis, 0, sizeof(vis));
/*	while (!q.empty()) q.pop();
	q.push(T), vis2[T] = true;
	while (!q.empty()) {
		int k = q.front(); q.pop();
		
		for (int i = G[k]; i != -1; i = E[i].nxt) {
			int x = E[i].to;
			if (vis2[x] || !E[i ^ 1].cap) continue;
			//cout << x << ' ' << E[i ^ 1].cap << endl;
			vis2[x] = true, q.push(x);
			
			if (x <= m + n) a[x - 1] = '0';
			else a[x - m - n - 1] = '1'; 
		}
	}
	*/
	for (int i = 0; i < m + n; ++i) 
		if (a[i] == '?') a[i] = '0';

	printf("%d\n", ans);
	for (int i = 0; i < m; ++i) putchar(a[i]);
	puts("");
	for (int i = m; i < m + n; ++i) putchar(a[i]);
	puts("");

	return 0;
}
