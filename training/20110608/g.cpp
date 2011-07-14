#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int n, d;
int deg[100010], a[100010];

int mk(int k) {
	if (k <= d) return 0;
	int t = k / d;
	return t + mk(t + k % d);
}

int main() {
	scanf("%d%d", &n, &d);
	memset(deg, 0, sizeof(deg));
	for (int i = 1; i <= n; ++ i) {
		scanf("%d", &a[i]);
		++ deg[a[i]];
	}
	int ans = 0;
	for (int i = 0; i <= n; ++ i) {
		ans += mk(deg[i]);
	}
	printf("%d\n", ans);
	return 0;
}

