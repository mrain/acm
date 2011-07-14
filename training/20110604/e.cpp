#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

template <class T>
inline T sqr(T a) { return a * a; }

int x[310], y[310], p[310];
int a, b, r, n, N, M;
vector <int> la, lb;
bool g[310][310];
bool vis[310];
int match[310];

inline int sgn(int x) {
	return x == 0 ? 0 : x > 0 ? 1 : -1;
}

int cross(int x1, int y1, int x2, int y2) {
	return x1 * y2 - x2 * y1; 
}

int same(int i, int j) {
	if (sgn(cross(x[i] - x[a], y[i] - y[a], x[b] - x[a], y[b] - y[a])) * 
		sgn(cross(x[j] - x[a], y[j] - y[a], x[b] - x[a], y[b] - y[a])) == -1)	
		return false;
	return true;
}

int dist(int i, int j) {
	return sqr(x[i] - x[j]) + sqr(y[i] - y[j]);
}

void init() {
	-- a, -- b;
	la.clear(), lb.clear();
	memset(g, 0, sizeof(g));
	int c = 0;
	while (!p[c]) ++ c;
	la.push_back(c);
	for (int i = 0; i < n; ++ i)
		if (p[i] && i != c) {
			if (same(i, c)) la.push_back(i);
			else lb.push_back(i);
		}
	if (la.size() > lb.size()) swap(la, lb);
	N = (int)la.size(); M = (int)lb.size();
	for (int i = 0; i < N; ++ i)
		for (int j = 0; j < M; ++ j)
			if (p[la[i]] > p[lb[j]] && dist(la[i], lb[j]) <= r * r)
				g[i][j] = true;
}

bool dfs(int u) {
	for (int v = 0; v < M; ++ v)
		if (!vis[v] && g[u][v]) {
			vis[v] = true;
			if (match[v] == -1 || dfs(match[v])) {
				match[v] = u;
				return true;
			}
		}
	return false;
}

int main() {
	int ca = 0;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; ++ i)
			scanf("%d%d%d", x + i, y + i, p + i);
		scanf("%d%d%d", &a, &b, &r);
		init();
		int ans = 0;
		memset(match, 0xFF, sizeof(match));
		for (int i = 0; i < N; ++ i) {
			memset(vis, 0, sizeof(vis));
			if (dfs(i)) ++ ans;
		}
		printf("Case %d: %d\n", ++ ca, ans);
	}
	return 0;
}
