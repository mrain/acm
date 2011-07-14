#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
const double eps = 1e-8;

inline double sgn(double a) {
	return a < -eps ? -1 : a > eps ? 1 : 0;
}

inline double sqr(double a) { return a * a; }

struct point {
	double x, y;
	point(double x = 0, double y = 0)
		: x(x), y(y) {}
};

point operator -(const point &a, const point &b) {
	return point(a.x - b.x, a.y - b.y);
}

double len(const point &a) {
	return sqrt(sqr(a.x) + sqr(a.y));
}

bool operator <(const point &a, const point &b) {
	if (sgn(a.x - b.x) == 0) return sgn(a.y - b.y) == -1;
	else return sgn(a.x - b.x) == -1;
}

int n;
point p[200010];

double work(int l, int r) {
	double ans = 1e9;
	int mid = (l + r) >> 1;
	if (l + 6 <= r)
		ans = min(work(l, mid), work(mid + 1, r));
	for (int i = l; i <= r; ++ i)
		for (int j = i + 1; j <= i + 5 && j <= r; ++ j)
			ans = min(ans, len(p[i] - p[j]));
	return ans;
}

int main() {
	cout.setf(ios::fixed);
	cout.precision(2);
	while (scanf("%d", &n), n) {
		for (int i = 0; i < n; ++ i)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		sort(p, p + n);
		cout << work(0, n - 1) * 0.5 << endl;
	}
	return 0;
}
