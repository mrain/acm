#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.);

inline int sgn(double a) {
	return a < -eps ? -1 : a > eps ? 1 : 0;
}

inline double sqr(double a) {
	return a * a;
}

struct point {
	double x, y;
	point(double x = 0, double y = 0)
		: x(x), y(y) {}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
};

point operator +(const point &a, const point &b) {
	return point(a.x + b.x, a.y + b.y);
}
point operator -(const point &a, const point &b) {
	return point(a.x - b.x, a.y - b.y);
}
point operator *(const point &a, const double &b) {
	return point(a.x * b, a.y * b);
}
point operator /(const point &a, const double &b) {
	return point(a.x / b, a.y / b);
}
inline double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}
inline double cross(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}
inline double norm(const point &a) {
	return dot(a, a);
}
inline double len(const point &a) {
	return sqrt(norm(a));
}

int n;
point c, a[100010];
double r;

bool init() {
	c = point(0, 0);
	if (scanf("%lf%d", &r, &n) != 2) return false;
	for (int i = 0; i < n; ++ i)
		a[i].read();
	a[n] = a[0];
	return true;
}

bool strict_in(double a, double b, double x) {
	return x > a + eps && x < b - eps;
}

ostream &operator <<(ostream &os, const point &a) {
	os << '(' << a.x << ',' << a.y << ')';
	return os;
}

int intersect(const point &a, const point &b, point &p, point &q) {
	double l = len(b - a);
	double d2 = dot(c - a, b - a) / len(b - a);
	double d1 = sqrt(norm(a - c) - sqr(d2));
	if (d1 > r - eps) return 0;
	double d3 = sqrt(sqr(r) - sqr(d1));
	point unit = (b - a) / l;
	double la = d2 - d3, lb = d2 + d3;
	if (strict_in(0, l, la)) {
		if (strict_in(0, l, lb)) {
			p = a + unit * la;
			q = a + unit * lb;
			return 2;
		} else {
			p = a + unit * la;
			return 1;
		}
	} else {
		if (strict_in(0, l, lb)) {
			p = a + unit * lb;
			return 1;
		}
		return 0;
	}
}

double calc(const point &a, const point &b) {
	double la = len(a - c), lb = len(b - c);
	if (max(la, lb) < r + eps) return 0.5 * cross(a - c, b - c);
	double xs = sgn(cross(a - c, b - c));
	double ang = acos(dot(a - c, b - c) / len(a - c) / len(b - c));
	if (xs == 0) return 0;
	point p, q;
	int cnt = intersect(a, b, p, q);
	if (cnt == 1) return calc(a, p) + calc(p, b);
	else if (cnt == 2) return calc(a, p) + calc(p, q) + calc(q, b);
	else return xs * sqr(r) / 2 * ang;
}

int main() {
	while (1) {
		if (!init()) break;
		double area = 0.;
		for (int i = 0; i < n; ++ i)
			area += calc(a[i], a[i + 1]);
		printf("%.2f\n", fabs(area));
	}
	return 0;
}

