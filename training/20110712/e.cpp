#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

int n, m, ans;
int father[20003];
int a[300000], b[300000];
int deg[30003];

inline int getf(int a) {
	if (father[a] == a) return a;
	else return father[a] = getf(father[a]);
}

bool cmp(int a, int b) {
	return deg[a] > deg[b];
}

int main() {
	while (scanf("%d%d", &n, &m)) {
		memset(deg, 0, sizeof(deg));
		if (n == 0 && m == 0) break;
		for (int i = 0; i < m; ++ i) {
			scanf("%d%d", &a[i], &b[i]);
		}
		ans = 0;
		for (int i = 0; i < n; ++ i) p[i] = i;
		sort(p, p + n, cmp);
		for (int k = 0; k < n; ++ k) {
			int r = p[k];
			for (int i = 0; i < n; ++ i) father[i] = i;
			int cnt = n - 1;
			for (int j = 0; j < m; ++ j) {
				if (a[j] == r || b[j] == r) continue;
				int fa = getf(a[j]), fb = getf(b[j]);
				if (fa != fb) {
					-- cnt;
					father[fa] = fb;
				}
				if (cnt <= ans) break;
			}
			ans = max(ans, cnt);
		}
		cout << ans << endl;
	}
	return 0;
}
