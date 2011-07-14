#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int storage[500000];
int *a[500000];
int f[500000], g[500000];
int n, m;

void remerge(int n, int m) {
	int *p = storage;
	for (int i = 0; i <= n; ++ i) {
		a[i] = p;
		p += m + 1;
	}
}

int work(int *a) {
	int ans = a[1];
	f[0] = 0; f[1] = a[1];
	for (int i = 2; i <= m; ++ i) {
		f[i] = max(f[i - 1], a[i] + f[i - 2]);
		ans = max(ans, f[i]);
	}
	return ans;
}

int main() {
	while (1) {
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0) break;
		remerge(n, m);
		for (int i = 1; i <= n; ++ i) {
			for (int j = 1; j <= m; ++ j)
				scanf("%d", &a[i][j]);
			g[i] = work(a[i]);
		}
		int ans = g[1];
		f[0] = 0; f[1] = g[1];
		for (int i = 2; i <= n; ++ i) {
			f[i] = max(f[i - 1], g[i] + f[i - 2]);
			ans = max(f[i], ans);
		}
		cout << ans << endl;
	}
	return 0;
}
