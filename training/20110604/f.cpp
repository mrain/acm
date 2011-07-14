#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

queue <int> q;
int vis[10010];
int a[20], l, u, r;

int main() {
	int ca = 0;
	while (scanf("%d%d%d", &l, &u, &r)) {
		if (l == 0 && u == 0 && r == 0) break;
		for (int i = 0; i < r; ++ i) {
			scanf("%d", &a[i]);
		}
		memset(vis, 0, sizeof(vis));
		vis[l] = 1;
		while (!q.empty()) q.pop();
		q.push(l);
		while (!q.empty()) {
			int now = q.front(); q.pop();
			for (int i = 0; i < r; ++ i) {
				int next = (now + a[i]) % 10000;
				if (!vis[next]) {
					vis[next] = vis[now] + 1;
					q.push(next);
				}
			}
			if (vis[u]) break;
		}
		printf("Case %d: ", ++ ca);
		if (!vis[u]) printf("Permanently Locked\n");
		else printf("%d\n", vis[u] - 1);
	}
	return 0;
}

