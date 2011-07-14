#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;
#define lowbit(x) ((x) & (-(x)))

int d[200010], n, a[200010];

void set(int p, int x) {
	int delta = x - a[p];
	a[p] = x;
	while (p <= n) {
		d[p] += delta;
		p += lowbit(p);
	}
}

int query(int a) {
	if (a <= 0) return 0;
	int ret = 0;
	while (a) {
		ret += d[a];
		a -= lowbit(a);
	}
	return ret;
}

int main() {
	int ca = 0;
	while (1) {
		memset(d, 0, sizeof(d));
		memset(a, 0, sizeof(a));
		scanf("%d", &n);
		if (!n) break;
		if (ca) puts("");
		for (int i = 1; i <= n; ++ i) {
			int t;
			scanf("%d", &t);
			set(i, t);
		}
		printf("Case %d:\n", ++ ca);
		char buf[4];
		while (1) {
			scanf("%s", buf);
			if (buf[0] == 'E') break;
			int a, b;
			scanf("%d%d", &a, &b);
			if (buf[0] == 'S') set(a, b);
			else printf("%d\n", query(b) - query(a - 1));
		}
	}
	return 0;
}

