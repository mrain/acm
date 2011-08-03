#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <complex>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.);
typedef complex<double> point;
typedef pair<point, point> segment;
typedef vector<point> polygon;

inline double sqr(double a) {
	return a * a;
}

inline double sgn(double a) {
	return a < -eps ? -1 : a > eps ? 1 : 0;
}

inline double dot(const point &a, const point &b) {
	return (a * conj(b)).real();
}

inline double cross(const point &a, const point &b) {
	return (b * conj(a)).imag();
}

bool inside(const point &a, const polygon &p) {
	double cnt = 0;
	for (int i = 0; i < (int)p.size() - 1; ++ i) {
		point x = p[i] - a, y = p[i + 1] - a;
		if (abs(x) == 0 || abs(y) == 0) return true;
		cnt += asin(cross(x, y) / abs(x) / abs(y));
	}
	return fabs(cnt) >= 2 * pi - eps;
}

inline bool intersect(const point &u1, const point &u2, const point &v1, const point &v2) {
	if (sgn(cross(u1 - v2, v1 - v2)) * sgn(cross(u2 - v2, v1 - v2)) >= 0) return false;
	if (sgn(cross(v1 - u2, u1 - u2)) * sgn(cross(v2 - u2, u1 - u2)) >= 0) return false;
	return true;
}

double dist(const point &p, const point &a, const point &b) {
	double l = dot(p - a, b - a) / abs(b - a);
	if (l <= eps || l >= abs(b - a) - eps) return min(abs(p - a), abs(p - b));
	return sqrt(sqr(abs(p - a)) - sqr(l));
}

bool polygonintersect(const polygon &a, const polygon &b) {
	for (int i = 0; i < (int)a.size() - 1; ++ i)
		if (inside(a[i], b)) return true;
	for (int i = 0; i < (int)b.size() - 1; ++ i)
		if (inside(b[i], a)) return true;
	for (int i = 0; i < (int)a.size() - 1; ++ i)
		for (int j = 0; j < (int)b.size() - 1; ++ j)
			if (intersect(a[i], a[i + 1], b[j], b[j + 1]))
				return true;
	return false;
}

double dist(const point &a, const polygon &b) {
	double ret = 1e100;
	for (int i = 0; i < (int)b.size() - 1; ++ i)
		ret = min(ret, dist(a, b[i], b[i + 1]));
	return ret;
}

double dist(const polygon &a, const polygon &b) {
	double ret = 1e100;
	for (int i = 0; i < (int)a.size() - 1; ++ i)
		for (int j = 0; j < (int)b.size() - 1; ++ j) {
			ret = min(ret, dist(a[i], b[j], b[j + 1]));
			ret = min(ret, dist(b[j], a[i], a[i + 1]));
		}
	return ret;
}

polygon a[110];
double w;
double d[110][110], d0[110], du[110], dd[110];
int n, f[110], upper, lower;

int getfather(int a) {
	return f[a] == a ? a : f[a] = getfather(f[a]);
}

void comb(int x, int y) {
	x = getfather(x), y = getfather(y);
	if (x != y) f[x] = y;
}

bool check(double r) {
	for (int i = 0; i < n; ++ i)
		if (d0[i] < r + eps)
			return false;
	for (int i = 0; i < n + 2; ++ i) f[i] = i;
	for (int i = 0; i < n; ++ i)
		if (du[i] < r + eps) comb(upper, i);
	for (int i = 0; i < n; ++ i)
		if (dd[i] < r + eps) comb(lower, i);
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j)
			if (d[i][j] < r + eps) comb(i, j);
	return getfather(upper) != getfather(lower);
}

int main() {
	while (scanf("%lf%d", &w, &n) == 2 && (sgn(w) || n)) {
		for (int i = 0; i < n; ++ i) {
			int k; scanf("%d", &k); a[i].clear();
			for (int j = 0; j < k; ++ j) {
				double x, y;
				scanf("%lf%lf", &x, &y);
				a[i].push_back(point(x, y));
			}
			a[i].push_back(a[i].front());
		}
		upper = n, lower = n + 1;
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < n; ++ j) {
				if (polygonintersect(a[i], a[j])) d[i][j] = 0.;
				else d[i][j] = dist(a[i], a[j]);
			}
		for (int i = 0; i < n; ++ i) {
			if (inside(point(0, 0), a[i])) d0[i] = 0.;
			else d0[i] = dist(point(0, 0), a[i]) * 2;
			du[i] = dd[i] = 1e100;
			for (int j = 0; j < (int)a[i].size() - 1; ++ j) {
				du[i] = min(du[i], w / 2 - a[i][j].imag());
				dd[i] = min(dd[i], w / 2 + a[i][j].imag());
			}
		}
		double l = 0, r = w;
		while (l + eps < r) {
			double mid = (l + r) * 0.5;
			if (check(mid)) l = mid;
			else r = mid;
		}
		if (!check(l)) puts("impossible");
		else printf("%.2f\n", l * 0.5);
	}
	return 0;
}

