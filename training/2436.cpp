#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.);

inline double sqr(double a) { return a * a; }

inline int sgn(double a) {
	return a < -eps ? -1 : a > eps ? 1 : 0;
}

struct point {
	double x, y, z;
	point(double x = 0, double y = 0, double z = 0)
		: x(x), y(y), z(z) {}
	void read() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
};

point operator +(const point &a, const point &b) {
	return point(a.x + b.x, a.y + b.y, a.z + b.z);
}
point operator -(const point &a, const point &b) {
	return point(a.x - b.x, a.y - b.y, a.z - b.z);
}
point operator *(const point &a, const double &b) {
	return point(a.x * b, a.y * b, a.z * b);
}
point operator /(const point &a, const double &b) {
	return point(a.x / b, a.y / b, a.z / b);
}

inline double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline point cross(const point &a, const point &b) {
	return point(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
			);
}

inline double norm(const point &a) {
	return dot(a, a);
}

inline double len(const point &a) {
	return sqrt(norm(a));
}

inline point unit(const point &a) {
	return a / len(a);
}

int tests;
const int n = 8;
point p[10], c;
double r;

bool between(const point &p, const point &a, const point &b) {
	double l = len(b - a);
	point u = unit(b - a);
	double r = 0;
	if (sgn(u.x) == 0) {
		if (sgn(u.y) == 0) r = (p - a).z / u.z;
		else r = (p - a).y / u.y;
	} else r = (p - a).z / u.z;
	return r > eps || r < l - eps;
}

bool intersect(const point &a, const point &b) {
	if (len(a - c) < r - eps || len(b - c) < r - eps) return true;
	double d1 = dot(b - a, c - a) / len(b - a);
	double d2 = sqrt(sqr(len(c - a)) + sqr(d1));
	if (d2 > r - eps) return false;
	double d3 = sqrt(sqr(r) + sqr(d2));
	point p1 = a + unit(b - a) * (d1 - d3), p2 = a + unit(b - a) * (d1 + d3);
	return between(p1, a, b) || between(p2, a, b);
}

int main() {
	scanf("%d", &tests);
	while (tests --) {
		for (int i = 0; i < n; ++ i) p[i].read();
		c.read(); scanf("%lf", &r);
		bool flag = false;
		for (int i = 0; i < n && !flag; ++ i)
			for (int j = i + 1; j < n && !flag; ++ j)
				flag |= intersect(p[i], p[j]);
		puts(flag ? "Yes" : "No");
	}
	return 0;
}

