#include <cstdio>
#include <queue>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <bitset>
#define two(x) (1<<(x)) 
using namespace std;

int tests, n, m, r;
vector <int> e[101];
int deg[101], sg[101], k[101];
queue <int> q;
vector <int> list;
bitset <80000> vis;
int bitcnt[80000];

void mksg(int i) {
	int l = (int)e[i].size();
	if (l == 0) return;
	vis.reset();
	for (int s = 1; s < two(l); ++ s) {
		if (bitcnt[s] > k[i]) continue;
		int t = 0;
		for (int j = 0; j < l; ++ j)
			if ((two(j) & s) != 0)
				t ^= sg[e[i][j]];
		vis.set(t);
	}
	while (vis.test(sg[i])) ++ sg[i];
}

int main() {
	for (int i = 1; i < two(16); ++ i)
		bitcnt[i] = bitcnt[i - (i & (-i))] + 1;
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < m; ++ i) {
			int a, b;
			scanf("%d%d", &a, &b);
			e[a].push_back(b);
			++ deg[b];
		}
		for (int i = 0; i < n; ++ i)
			scanf("%d", &k[i]);
		while (!q.empty()) q.pop();
		for (int i = 0; i < n; ++ i)
			if (!deg[i]) q.push(i);
		list.clear();
		while (!q.empty()) {
			int u = q.front(); q.pop();
			list.push_back(u);
			for (int i = 0; i < (int)e[u].size(); ++ i) {
				-- deg[e[u][i]];
				if (!deg[e[u][u]]) q.push(e[u][i]);
			}
		}
		reverse(list.begin(), list.end());
		memset(sg, 0, sizeof(sg));
		for (int i = 0; i < (int)list.size(); ++ i)
			mksg(list[i]);
		printf("Game#%d:\n", ++ ca);
		scanf("%d", &r);
		for (int round = 1; round <= r; ++ round) {
			int res = 0;
			for (int i = 0; i < n; ++ i) {
				int a;
				scanf("%d", &a);
				if ((a & 1) == 1) res ^= sg[i];
			}
			printf("Round#%d: %s\n", round, res == 0 ? "LOSING" : "WINNING");
		}
		puts("");
	}
	return 0;
}

