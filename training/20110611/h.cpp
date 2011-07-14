#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

const int m = 26;
bool f[20000][30];
bool avai[20000][30];
vector <int> e[20000];
char buf[1000];
int n, N, g[30][30];
int match[30];
int vis[30];

void init(int k) {
	e[k].clear();
	while (gets(buf)) {
		if (buf[0] == '>') break;
		if (buf[0] == '<')
			init(e[k].back());
		else {
			e[k].push_back(n);
			int l = strlen(buf);
			for (int i = 0; i < l; ++ i)
				if (isupper(buf[i])) avai[n][int(buf[i] - 'A')] = true;
			++ n;
		}
	}
}

bool find(int u) {
	for (int v = 0; v < m; ++ v)
		if (vis[v] < u && g[u][v]) {
			vis[v] = u;
			if (match[v] == -1 || find(match[v])) {
				match[v] = u;
				return true;
			}
		}
	return false;
}

bool dfs(int n, int use) {
	if ((int)e[n].size() > m) return f[n][use] = false;
	for (int i = 0; i < (int)e[n].size(); ++ i)
		for (int j = 0; j < m; ++ j)
			if (avai[e[n][i]][j])
				f[e[n][i]][j] = dfs(e[n][i], j);
	memset(g, 0, sizeof(g));
	memset(match, -1, sizeof(match));
	N = (int)e[n].size();
	for (int i = 0; i < N; ++ i)
		for (int j = 0; j < m; ++ j)
			if (j != use) g[i][j] = f[e[n][i]][j];
	memset(vis, 0xFF, sizeof(vis));
	for (int i = 0; i < N; ++ i) {
		if (!find(i)) return f[n][use] = false;
	}
	return f[n][use] = true;
}

int main() {
	memset(avai, 0, sizeof(avai));
	gets(buf), n = 1;
	init(0);
	puts(dfs(0, 30) ? "Got It!" : "No Solution");
	return 0;
}

