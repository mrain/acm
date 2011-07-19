#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int tests, n, m;
int a[200][200], b[200][200], c[200][200];

int main() {
	scanf("%d", &tests);
	while (tests --) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < m; ++ j)
				scanf("%d", &a[i][j]);
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < m; ++ j)
				scanf("%d", &b[i][j]);
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < m; ++ j)
				scanf("%d", &c[i][j]);
		long long ans = 0;
		for (int i = 0; i < n; ++ i) {
			long long tmp = 0;
			for (int j = 0; j < m; ++ j)
				tmp = max(tmp, (long long)min(a[i][j], b[i][j]) * (long long)c[i][j]);
			ans += tmp;
		}
		cout << ans << endl;
	}
	return 0;
}
