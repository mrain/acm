#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

int tests, n, m, len;
typedef pair<int, int> PII;
vector <pair<int, int> > a[100];
vector <int> w[100];
char s[300], buf2[300], buf3[300];
int times;
int vis[110][110][27], f[110][110][27];

int dp(int l, int r, int k) {
	if (l == r) return f[l][r][k] = (s[l] == (k + 'a') ? 1 : -1);
	if (vis[l][r][k] == times) return f[l][r][k];
	vis[l][r][k] = times;
	f[l][r][k] = -1;
	for (int i = 0; i < (int)a[k].size(); ++ i) {
		int p = a[k][i].first, q = a[k][i].second, cost = w[k][i];
		for (int mid = l; mid < r; ++ mid) {
			int ra = dp(l, mid, p), rb = dp(mid + 1, r, q);
			if (ra == -1 || rb == -1) continue;
			if (f[l][r][k] == -1 || f[l][r][k] > ra + rb + cost)
				f[l][r][k] = ra + rb + cost;
		}
	}
	return f[l][r][k];
}

int main() {
	scanf("%d", &tests);
	times = 0;
	int ca = 0;
	while (tests --) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < 26; ++ i)
			a[i].clear(), w[i].clear();
		for (int i = 0; i < n; ++ i) {
			int cost;
			scanf("%s%s%s%d", s, buf2, buf3, &cost);
			a[s[0] - 'A'].push_back(make_pair(buf2[0] - 'A', buf3[0] - 'A'));
			w[s[0] - 'A'].push_back(cost);
		}
		printf("CASE #%d\n", ++ ca);
		for (int i = 0; i < m; ++ i) {
			++ times;
			scanf("%d%s", &len, s);
			int ret = dp(0, len - 1, 0);
			if (ret == -1) puts("IMPOSSIBLE");
			else printf("POSSIBLE WITH %d DIAMONDS\n", ret);
		}
	}
	return 0;
}
