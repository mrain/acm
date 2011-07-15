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

struct line{
	int A, B, C;
	// Ax + By + C = 0
	line(int A = 0, int B = 0, int C = 0)
		: A(A), B(B), C(C) {}
	line(const point &a, const point &b) {
		A = b.y - a.y;
		B = a.x - b.x;
		C = cross(b, a);
	}
};

//两条线段是否严格相交
bool isintersect(const point &u1, const point &u2, const point &v1, const point &v2) {
	if (sgn(cross(v1 - u1, u2 - u1)) * sgn(cross(v2 - u1, u2 - u1)) != -1) return false;
	if (sgn(cross(u1 - v1, v2 - v1)) * sgn(cross(u2 - v1, v2 - v1)) != -1) return false;
	return true;
}

//求两条直线交点
point intersect(const point &u1, const point &u2, const point &v1, const point &v2) {
	if (sgn(cross(u1 - u2, v1 - v2)) == 0) throw 0;
	double t = cross(u1 - v1, v1 - v2) / cross(u1 - u2, v1 - v2);
	return u1 + (u2 - u1) * t;
}

int main() {
	return 0;
}
