#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int tests, val[200000], n;

inline int log(int a) {
	int ret = 0;
	while (a) {
		a /= 10;
		++ ret;
	}
	return ret;
}

void output(int a, int b, int k) {
	putchar('0');
	printf("%d", a);
	if (a == b) {
		puts("");
		return;
	}
	putchar('-');
	int p = 1;
	for (int i = 0; i < k; ++ i)
		p *= 10;
	printf("%d\n", b % p);
}

inline int cmp(int a, int b) {
	int ret = 0;
	while (a % 10 != b % 10) {
		++ ret;
		a /= 10, b /= 10;
	}
	return ret;
}

int main() {
	int ca = 0;
	while (true) {
		scanf("%d", &n);
		if (!n) break;
		for (int i = 0; i < n; ++ i)
			scanf("%d", &val[i]);
		printf("Case %d:\n", ++ ca);
		for (int i = 0; i < n;) {
			int j = i + 1, k = 0;
			while (j < n && val[j] == val[j - 1] + 1) {
				k = max(k, cmp(val[j], val[j - 1]));
				++ j;
			}
			output(val[i], val[j - 1], k);
			i = j;
		}
		puts("");
	}
	return 0;
}

