#include <cstdio>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.);

inline int sgn(double a) { return a < -eps ? -1 : a > eps ? 1 : 0; }
inline double sqr(double a) { return a * a; }

struct point {
	double x, y, z;
	point(double x = 0, double y = 0, double z = 0)
		: x(x), y(y), z(z) {}
};
inline point operator +(const point &a, const point &b) {
	return point(a.x + b.x, a.y + b.y, a.z + b.z);
}
inline point operator -(const point &a, const point &b) {
	return point(a.x - b.x, a.y - b.y, a.z - b.z);
}
inline point operator *(const point &a, const double &b) {
	return point(a.x * b, a.y * b, a.z * b);
}
inline point operator /(const point &a, const double &b) {
	return point(a.x / b, a.y / b, a.z / b);
}
inline double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
inline point cross(const point &a, const point &b) {
	return point(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x );
}
inline double abs(const point &a) {
	return sqrt(dot(a, a));
}

struct point2d {
	double x, y;
	point2d(double x = 0, double y = 0)
		: x(x), y(y) {}
};
inline double cross(const point2d &a, const point2d &b) {
	return a.x * b.y - a.y * b.x;
}
inline double ang(const point2d &a) {
	return atan2(a.y, a.x);
}
inline point2d operator -(const point2d &a, const point2d &b) {
	return point2d(a.x - b.x, a.y - b.y);
}
inline double abs(const point2d &a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

point x, y, z, p[110], s, base;
double a, b, c, d;
int n, top;
bool flag;
vector <point2d> l;
point2d stack[110];

inline bool cmp(const point2d &a, const point2d &b) {
	if (ang(a - l[0]) == ang(b - l[0])) return abs(a - l[0]) < abs(b - l[0]);
	else return ang(a - l[0]) < ang(b - l[0]);
}

void init() {
	z = point(a, b, c); z = z / abs(z);
	if (sgn(a)) {
		x = point((d - b) / a, 1, 0);
		y = point((d - c) / a, 0, 1);
	} else if (sgn(b)) {
		x = point(1, (d - a) / b, 0);
		y = point(0, (d - c) / b, 1);
	} else if (sgn(c)) {
		x = point(1, 0, (d - a) / c);
		y = point(0, 1, (d - b) / c);
	}
	base = x;
	x = cross(y - x, z); y = cross(x, z);
	x = x / abs(x), y = y / abs(y);

	double sign = 1; l.clear();
	s = s - base;
	s = point(dot(s, x), dot(s, y), dot(s, z));
//	printf("%.4f %.4f %.4f\n", s.x, s.y, s.z);
	if (s.z < 0) sign = -1, s.z *= -1;
	for (int i = 0; i < n; ++ i) {
//		printf("%.4f %.4f %.4f\n", p[i].x, p[i].y, p[i].z);
		p[i] = p[i] - base;
		p[i] = point(dot(p[i], x), dot(p[i], y), dot(p[i], z) * sign);
		if (p[i].z < -eps) continue;
//		printf("%.4f %.4f %.4f\n", p[i].x, p[i].y, p[i].z);
		if (p[i].z > s.z - eps) flag = true;
		else {
			point dir = p[i] - s;
			double l1 = abs(dir); dir = dir / l1;
			double l2 = l1 * p[i].z / (s.z - p[i].z);
			dir = p[i] + dir * l2;
			l.push_back(point2d(dir.x, dir.y));
//			printf("%.4f %.4f\n", dir.x, dir.y);
		}
	}
}

int main() {
	while (scanf("%lf %lf %lf %lf\n", &a, &b, &c, &d) == 4) {
		if (!sgn(a) && !sgn(b) && !sgn(c) && !sgn(d)) break;
		scanf("%d", &n);
		for (int i = 0; i < n; ++ i)
			scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z);
		scanf("%lf%lf%lf", &s.x, &s.y, &s.z);
		flag = false; init();

		if (l.size() == 0) puts("0.00");
		else if (flag) puts("Infi");
		else {
			for (int i = 1; i < (int)l.size(); ++ i)
				if (l[i].y < l[0].y - eps || (sgn(l[i].y - l[0].y) == 0 && l[i].x < l[0].x - eps))
					swap(l[i], l[0]);
			sort(l.begin() + 1, l.end(), cmp);
//			for (int i = 0; i < (int)l.size(); ++ i) printf("%.4f %.4f\n", l[i].x, l[i].y);
			stack[0] = l[0]; top = 0;
			for (int i = 1; i < (int)l.size(); ++ i) {
				while (top > 1 && cross(stack[top] - stack[top - 1], l[i] - stack[top]) < eps) -- top;
				stack[++ top] = l[i];
			}
			while (top > 1 && cross(stack[top] - stack[top - 1], l[0] - stack[top]) < eps) -- top;
//			for (int i = 0; i <= top; ++ i) printf("%.4f %.4f\n", stack[i].x, stack[i].y);
			double ans = cross(stack[top], stack[0]);
			for (int i = 0; i < top; ++ i) ans += cross(stack[i], stack[i + 1]);
			printf("%.2f\n", fabs(ans) / 2);
		}
	}
	return 0;
}

