#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

int deg[600], n, c, father[600];
vector <int> belong[600], id[600];

int getfather(int a) {
	if (father[a] != a) return father[a] = getfather(father[a]);
	else return a;
}

bool comb(int a, int b) {
	int fa = getfather(a), fb = getfather(b);
	if (fa == fb) return false;
	father[fa] = fb;
	return true;
}

int check(int block) {
	int tot = n;
	for (int i = 0; i < n; ++ i) father[i] = i;
	for (int i = 0; i < c; ++ i) {
		if (deg[i] < 2) continue;
		int p = id[i][0];
		if (p == block)
			p = id[i][1];
		for (int j = 0; j < deg[i]; ++ j)
			if (id[i][j] != block && comb(p, id[i][j]))
				-- tot;
	}
//	cout << block << ' ' << tot << endl;
	return tot;
}

int main() {
	while (1) {
		scanf("%d%d", &n, &c);
		if (n == 0 && c == 0) break;
		memset(deg, 0, sizeof(deg));
		for (int i = 0; i < n; ++ i) belong[i].clear();
		for (int i = 0; i < c; ++ i) id[i].clear();
		for (int i = 0; i < c; ++ i) {
			int t, k;
			scanf("%d", &t);
			for (int j = 0; j < t; ++ j) {
				scanf("%d", &k);
				belong[k].push_back(i);
			}
		}
		for (int i = 0; i < n; ++ i) {
			if (belong[i].size() != 2) belong[i].push_back(belong[i][0]);
			int a = belong[i][0], b = belong[i][1];
			++ deg[a], ++ deg[b];
			id[a].push_back(i);
			id[b].push_back(i);
		}
		int tot = 0;
		int ans = 12345;
		for (int i = 0; i < c; ++ i)
			if (deg[i] & 1)
				++ tot;
		if ((tot != 0 && tot != 2) || check(n) > 1) {
			puts("-1");
			continue;
		}
		if (tot == 0) {
			for (int i = 0; i < n; ++ i)
				if (check(i) <= 2) ans = min(ans, i);
		} else {
			for (int i = 0; i < c; ++ i)
				if (deg[i] & 1) {
					for (int j = 0; j < deg[i]; ++ j)
						if (check(id[i][j]) <= 2)
							ans = min(ans, id[i][j]);
				}
		}
		if (ans == 12345) ans = -1;
		printf("%d\n", ans);
	}
	return 0;
}

