#include <cstdio>
#include <cmath>
#include <cstdlib>

double r, x[101], y[101];
int n;
double pi = acos(-1.0), ans;

inline double sqr(double x) { return x * x; }

int main() {
	scanf("%d%lf", &n, &r);
	ans = 0;
	for (int i = 0; i < n; ++ i) {
		scanf("%lf%lf", &x[i], &y[i]);
		if (i) ans += sqrt(sqr(x[i] - x[i - 1]) + sqr(y[i] - y[i - 1]));
	}
	ans += sqrt(sqr(x[n - 1] - x[0]) + sqr(y[n - 1] - y[0]));
	ans += 2 * pi * r;
	printf("%.2f\n", ans);
	return 0;
}
