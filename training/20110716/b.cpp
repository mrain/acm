#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
#define two(x) (1<<(x))

long long cnt[9][two(9)];
bool vis[9][two(9)];
int n, bitcnt[two(9)], log[two(10)];
char g[10][10];
bool conn[two(9)][two(9)];

bool check(int a, int b) {
	for (int j = 0; j < n; ++ j)
		if ((two(j) & b) && g[a][j] == '0')
			return false;
	return true;
}

int dp(int, int);

int dfs(int a, int s) {
	if (s == 0) return 1;
	if (a == 0) return 0;
	int k = log[a & (-a)];
	int ret = dfs(a - two(k), s);
	for (int t = s; t; t = (t - 1) & s)
		ret += dfs(a - two(k), s - t) * dp(k, t);
	return ret;
}

int dp(int root, int s) {
	if (s == 0) return 1;
	if (vis[root][s]) return cnt[root][s];
	vis[root][s] = true;
	cnt[root][s] = 0;
	for (int a = s; a; a = (a - 1) & s) {
		if (!conn[root][a]) continue;
		int rest = s - a;
//		if (root == 0 && s == 14) cout << a << ' ' << rest << ' ' << dfs(a, rest) << endl;
		cnt[root][s] += dfs(a, rest);
	}
	return cnt[root][s];
}

int main() {
	bitcnt[0] = 0;
	for (int i = 1; i < two(9); ++ i)
		bitcnt[i] = bitcnt[i - (i&(-i))] + 1;
	for (int i = 0; i < 10; ++ i)
		log[two(i)] = i;
	while (scanf("%d", &n), n) {
		for (int i = 0; i < n; ++ i) scanf("%s", g[i]);
		memset(conn, 0, sizeof(conn));
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < two(n); ++ j)
				conn[i][j] = check(i, j);
		int ans = 0;
		for (int i = 0; i < n; ++ i) {
//			int t = dp(i, two(n) - 1 - two(i));
//			cout << i << ' ' << t << endl;
			memset(vis, 0, sizeof(vis));
			memset(cnt, 0, sizeof(cnt));
			ans += dp(i, two(n) - 1 - two(i));
		}
		cout << ans << endl;
	}
	return 0;
}

