#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

/*map<int, int> f[10001];
int vis[10010], times;

void calc(int n) {
	f[n].clear();
	for (int i = 0; i < n; ++ i) {
		int cnt = 0; ++ times;
		for (int s = 0; s < n; ++ s) {
			if (vis[s] == times) continue;
			int x = s; ++ cnt;
			while (vis[x] != times) {
				vis[x] = times;
				x = n - x - 1;
				x = (x + i) % n;
			}
		}
		++ f[n][cnt];
	}
}*/

const int mod = 1000000007;
int n, m, tests;

int pow(int a, int v) {
	int ret = 1;
	while (v) {
		if (v & 1) ret = 1ll * ret * a % mod;
		a = 1ll * a * a % mod; v >>= 1;
	}
	return ret;
}

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
/*	for (int i = 1; i <= 100; ++ i) {
		calc(i);
		cout << "!!!" << i << endl;
		for (map<int, int>::iterator it = f[i].begin(); it != f[i].end(); ++ it) {
			printf("%d %d\n", it->first, it->second);
		}
	}*/
	scanf("%d", &tests);
	for (int ca = 1; ca <= tests; ++ ca) {
		scanf("%d %d", &n, &m);
		if (m == 1) {
			printf("Case #%d: %d\n", ca, n);
			continue;
		}
		if (m == 2) {
			printf("Case #%d: %d\n", ca, n + n * (n - 1) / 2);
			continue;
		}
		int rev = pow(2 * m, mod - 2), ans = 0;
		if (m & 1) ans = 1ll * m * pow(n, (m + 1) / 2) % mod;
		else {
			ans = 1ll * (m / 2) * pow(n, m / 2) % mod;
//			ans = ((long long)ans + (long long)ans * n % mod) % mod;
			ans = 1ll * ans * (n + 1) % mod;
		}
		for (int i = 0; i < m; ++ i) {
			int tmp = pow(n, gcd(i, m));
			ans = ((long long)ans + tmp) % mod;
		}
//		printf("%d\n", ans);
		ans = 1ll * ans * rev % mod;
		printf("Case #%d: %d\n", ca, ans);
	}
	return 0;
}

