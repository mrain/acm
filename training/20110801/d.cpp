#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;

int tests, n, a[1001];

int main() {
	scanf("%d", &tests);
	while (tests --) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++ i)
			scanf("%d", a + i);
		sort(a, a + n);
		int ans = 0;
		for (int i = 0; i < n; ++ i) {
			if (a[i] > ans + 1) break;
			ans += a[i];
		}
		printf("%d\n", ans + 1);
	}
	return 0;
}

