#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;
int tests, n, f[1010];
PII l[1010];

int main() {
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++ i)
			scanf("%d%d", &l[i].first, &l[i].second);
		sort(l, l + n);
		for (int k = 0; k < n;) {
			int i = k, cnt = 0;
			while (i < n && l[i].first == l[k].first) ++ i; -- i;
			for (int next = i; next >= 0; ) {
				int j = next;
				while (j >= 0 && l[j].first == l[next].first) {
					if (l[j].second >= l[i].first) ++ cnt;
					-- j;
				}
				f[i] = max(f[i], (j < 0 ? 0 : f[j]) + (cnt > 2 ? cnt : 0));
				next = j;
			}
			k = i + 1;
		}
		printf("Case #%d: %d\n", ++ ca, f[n - 1]);
	}
	return 0;
}

