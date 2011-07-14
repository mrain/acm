#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

int f[50010], l[50010], n, m;

bool check(int p) {
	int cnt = 0;
	for (int i = 0; i < m; ++ i)
		cnt += l[i] / p;
	return cnt >= n;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++ i)
		scanf("%d", l + i);
	f[0] = 2147483647;
	int L = 0, R = n;
	while (L < R - 1) {
		int mid = (L + R) >> 1;
		if (check(mid)) L = mid;
		else R = mid - 1;
	}
	if (check(R)) L = R;
	printf("%d\n", L);
	int cnt = n;
	for (int i = 0; i < m; ++ i) {
		int t = min(l[i] / L, cnt);
		cnt -= t;
		for (int j = 0; j < t; ++ j)
			printf("%d\n", i + 1);
	}
	return 0;
}

