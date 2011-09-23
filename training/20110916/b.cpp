#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const double pi = acos(-1.);
double w, h, sx, sy, ex, ey, ans;
int n;

double ang(double y, double x) {
	double k = atan2(y, x);
	if (k < 1e-8) k += 2 * pi;
	return k;
}

void dfs(int d, double ex, double ey, double b, double t, double l, double r) {
	double tmp = ang(sx - ey, sy - ey);
	if (ans > tmp) ans = tmp;

	if (d == n) return;
	dfs(d + 1, 2 * l - ex, ey, b, t, 2 * l - r, r);

	dfs(d + 1, ex, 2 * b - ey, 2 * b - t, t, l, r);

	dfs(d + 1, 2 * r - ex, ey, b, t, l, 2 * r - l);

	dfs(d + 1, ex, 2 * t - ey, b, 2 * t - b, l, r);
}

int main() {
	scanf("%lf%lf%d%lf%lf%lf%lf", &w, &h, &n, &ex, &ey, &sx, &sy);
	ans = 1e100;
	dfs(1, ex, ey, 0, h, 0, w);
	printf("%.2f\n", ans / pi * 180.);
	return 0;
}

