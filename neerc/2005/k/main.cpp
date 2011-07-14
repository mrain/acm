#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#define Eps 1e-9
using namespace std;

const double pi = acos(-1.);
inline int sgn(double a) {
	return a < -Eps ? -1 : a > Eps ? 1 : 0;
}
inline double sqr(double a) { return a * a; }

struct Point {
	double x, y, z;
	Point(double x = 0, double y = 0, double z = 0)
		: x(x), y(y), z(z) {}
	Point operator *(const double &t) const{ return Point(x * t, y * t, z * t); }
	Point operator /(const double &t) const{ return Point(x / t, y / t, z / t); }
	Point operator +(const Point &t) const{ return Point(x + t.x, y + t.y, z + t.z); }
	Point operator -(const Point &t) const{ return Point(x - t.x, y - t.y, z - t.z); }
	double dot(const Point &t) { return x * t.x + y * t.y + z * t.z; }
	Point cross(const Point &t) {
		return Point(
				y * t.z - z * t.y,
				z * t.x - x * t.z,
				x * t.y - y * t.x
				);
	}
	double norm() { return x * x + y * y + z * z; }
	double abs() { return sqrt(norm()); }
	Point unit() { 
		if (abs() < Eps) return *this;
		return *this / abs();
	}
};

ostream &operator <<(ostream &os, Point t) {
	return os << '(' << t.x << ", " << t.y << ", " << t.z << ')';
}

int n;
Point p[50];

double result(const Point &t) {
	double ret = 1e100;
	for (int i = 0; i < n; ++ i) {
		double d = (p[i] - t).abs() / 2;
		if (d > 1) d = 1;
		ret = min(ret, 2 * asin(d));
	}
	return ret;
}

int main() {
//	freopen("input.txt", "r", stdin);
	while (scanf("%d", &n) == 1) {
		if (n == 1) {
			printf("%.6f\n", pi);
			continue;
		}
		for (int i = 0; i < n; ++ i) {
			double lat, lon;
			scanf("%lf%lf", &lat, &lon);
			lat = lat / 180 * pi; lon = lon / 180 * pi;
			p[i] = Point(cos(lat) * cos(lon), cos(lat) * sin(lon), sin(lat));
		}
		double ans = 0;
		for (int i = 0; i < n; ++ i)
			for (int j = i + 1; j < n; ++ j) {
				Point t = p[i] + p[j];
				if (t.abs() < Eps) {
					if (p[i].x < 1 - Eps) t = Point(0, -p[i].z, p[i].y);
					else if (p[i].y < 1 - Eps) t = Point(-p[i].z, 0, p[i].x);
					else if (p[i].z < 1 - Eps) t = Point(-p[i].y, p[i].x, 0);
				}
				t = t.unit();
				ans = max(ans, result(t));
				ans = max(ans, result(t * -1));
			}
		for (int i = 0; i < n; ++ i)
			for (int j = i + 1; j < n; ++ j)
				for (int k = j + 1; k < n; ++ k) {
					Point t = (p[j] - p[i]).cross(p[k] - p[i]).unit();
					ans = max(ans, result(t));
					ans = max(ans, result(t * -1));
				}
		printf("%.6f\n", ans);
	}
	return 0;
}
