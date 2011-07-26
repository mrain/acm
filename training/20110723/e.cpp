#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int n, w, m;
double vk, s[1000010], x[100010], y[100010];

bool check(double s) {
	double l = x[0], r = l + w;
	for (int i = 1; i < n; ++ i) {
		double d = (y[i] - y[i - 1]) / s * vk;
		l = max(l - d, x[i]);
		r = min(r + d, x[i] + w);
		if (l > r + 1e-8) return false;
	}
	return true;
}

int main() {
	scanf("%d%lf%d", &w, &vk, &n);
	for (int i = 0; i < n; ++ i)
		scanf("%lf%lf", &x[i], &y[i]);
	scanf("%d", &m);
	for (int i = 0; i < m; ++ i)
		scanf("%lf", s + i);
	sort(s, s + m);
	int l = 0, r = m - 1;
	while (l < r) {
		int mid = (l + r + 1) >> 1;
		if (!check(s[mid])) r = mid - 1;
		else l = mid;
	}
	if (!check(s[r])) puts("IMPOSSIBLE");
	else printf("%.0f\n", s[l]);
	return 0;
}
