#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-8;
int sgn(double a) {
	return a < -eps ? -1 : a > eps ? 1 : 0;
}

struct Point {
	double x, y;
	Point(double a = 0, double b = 0) : x(a), y(b) {}
	Point operator +(const Point &a) const {
		return Point(x + a.x, y + a.y);
	}
	Point operator -(const Point &a) const {
		return Point(x - a.x, y - a.y);
	}
	Point operator *(const double &a) const {
		return Point(x * a, y * a);
	}
	Point operator /(const double &a) const {
		return Point(x / a, y / a);
	}
	Point rotate(double r) {
		return Point(
				x * cos(r) - y * sin(r),
				x * sin(r) + y * cos(r)
			);
	}
};

double dot(const Point &a, const Point &b) {
	return a.x * b.x + a.y * b.y;
}

double cross(const Point &a, const Point &b) {
	return a.x * b.y - a.y * b.x;
}

Point mk(Point a, Point b, Point c, Point d) {
	double a1 = b.y - a.y;
	double b1 = -(b.x - a.x);
	double c1 = - a.x * b.y + a.y * b.x;
	double a2 = d.y - c.y;
	double b2 = -(d.x - c.x);
	double c2 = - c.x * d.y + c.y * d.x;
	Point ret;
	ret.y = -(c1 * a2 - c2 * a1) / (b1 * a2 - b2 * a1);
	if (sgn(a1) <= 0) ret.x = (- c2 - ret.y * b2) / a2;
	else ret.x = (- c1 - ret.y * b1) / a1;
	return ret;
}

Point a, b, c;
int tests;

int main() {
	cin >> tests;
	while (tests --) {
		cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
		if (cross(b - a, c - a) > 0) swap(c, b);
		Point d = a + (b - a).rotate(pi / 2);
		Point e = b + (a - b).rotate(-pi / 2);
		Point g = a + (c - a).rotate(-pi / 2);
		Point f = c + (a - c).rotate(pi / 2);
		Point h = c + (b - c).rotate(-pi / 2);
		Point j = b + (c - b).rotate(pi / 2);
		Point l = (g + d) / 2;
		Point m = (e + j) / 2;
		Point n = (f + h) / 2;
		Point res = mk(a, l, c, n);
		if (sgn(res.x) == 0) res.x = 0;
		if (sgn(res.y) == 0) res.y = 0;
		printf("%.4f %.4f\n", res.x, res.y);
	}
	return 0;
}

