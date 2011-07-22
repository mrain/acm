#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int n, A, B;
double p;

double calc(int x) {
	if (fabs(p) <= 1e-8) return 0;
	int y = n - x;
	return x * p * A + (pow(1. - p, y) + y * p - 1.) / p * B;
}

int main() {
	while (1) {
		scanf("%d%lf%d%d", &n, &p, &A, &B);
		if (n == 0 && fabs(p) <= 1e-8 && A == 0 && B == 0) break;
		p /= 100.;
		double l = 0, r = n;
		while (l + 10 < r) {
			int c = l + (r - l) / 3;
			int d = r - (r - l) / 3;
			double fc = calc(c), fd = calc(d);
			if (fc < fd) r = d;
			else l = c;
		}
		double ans = 1e10;
		for (int i = l; i <= r; ++ i)
			ans = min(ans, calc(i));
		printf("%.10f\n", ans);
	}
	return 0;
}
