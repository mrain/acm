#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;

int tests, n, k;
long long a[50], s[50], ans;//, fcmp, b[50][50], sb[50][50];
bool vis[50];

void dfs(int d, int cnt, long long res) {
	if (n - d + cnt < k) return;
	if ((res & s[d]) >= ans) return;
	if ((res & s[d]) == res) cnt = k;
	if (cnt == k) {
		ans = min(ans, res);
		return;
	}
	dfs(d + 1, cnt + 1, res & a[d]);
	dfs(d + 1, cnt, res);
}

void dfs2(int cnt, long long res) {
//	sort(b[cnt], b[cnt] + n - cnt);
	if (cnt == k) {
		ans = min(ans, res);
//		ans = min(ans, b[cnt][0]);
		return;
	}
//	for ()
//	fcmp = res;
//	sort(a + cnt, a + n, cmp);
	int choose = -1;
	long long tmp = (~0llu) >> 1;
	for (int i = 0; i < n; ++ i) {
		if (vis[i]) continue;
		if ((res & a[i]) < tmp) {
			tmp = res & a[i];
			choose = i;
		}
	}
	vis[choose] = true;
	dfs2(cnt + 1, res & a[choose]);
	vis[choose] = false;
}

int main() {
	cin >> tests;
	int ca = 0;
	while (tests --) {
		cin >> n >> k;
		for (int i = 0; i < n; ++ i)
			cin >> a[i];
		sort(a, a + n); //reverse(a, a + n);
		s[n - 1] = a[n - 1];
		for (int i = n - 2; i >= 0; -- i) s[i] = s[i + 1] & a[i];
		ans = (~0llu>>1);
//		dfs
//		dfs2(0, (~0llu)>>1);
		dfs(0, 0, (~0llu>>1));
//		memcpy(b[0], a, sizeof(a));
		cout << "Case #" << ++ ca << ": " << ans << endl;
	}
	return 0;
}

