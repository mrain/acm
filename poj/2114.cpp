#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

typedef set<int>::iterator IT1;
typedef map<int, int>::iterator IT2;
int n, m;
vector <int> e[20003], w[20003];
set <int> app[20003];
map <int, int> hash;
bool found[103], vis[20003];

void dfs(int u) {
	app[u].insert(0);
	vis[u] = true;
	for (int i = 0; i < (int)e[u].size(); ++ i) {
		int v = e[u][i], c = w[u][i];
		if (vis[v]) continue;
		dfs(v);
		for (IT2 b = hash.begin(); b != hash.end(); ++ b) {
			if (found[b->second]) continue;
			for (IT1 a = app[v].begin(); a != app[v].end(); ++ a)
				if (app[u].count(b->first - (*a + c))) {
					found[b->second] = true;
					break;
				}
		}
		for (IT1 a = app[v].begin(); a != app[v].end(); ++ a)
			app[u].insert(*a + c);
		app[v].clear();
	}
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		hash.clear();
		for (int i = 0; i < n; ++ i) e[i].clear(), app[i].clear();
		for (int i = 0; i < n; ++ i) {
			int c, d;
			while (scanf("%d", &c) == 1 && c) {
				scanf("%d", &d);
				e[i].push_back(c - 1);
				w[i].push_back(d);
				e[c - 1].push_back(i);
				w[c - 1].push_back(d);
			}
		}
		int need; m = 0;
		while (scanf("%d", &need), need)
			hash[need] = m ++;
		memset(found, 0, sizeof(found));
		memset(vis, 0, sizeof(vis));
		dfs(0);
		for (int i = 0; i < m; ++ i)
			puts(found[i] ? "AYE" : "NAY");
		puts(".");
	}
	return 0;
}
