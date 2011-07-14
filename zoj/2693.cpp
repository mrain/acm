#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

inline double sqr(double a) { return a * a; }
inline double SQRT(double a) { return a < 0 ? 0 : sqrt(a); }

struct Point{
	double x, y, z;
	Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
	Point operator *(const double &a) const {
		return Point(a * x, a * y, a * z);
	}
	Point operator +(const Point &t) const {
		return Point(x + t.x, y + t.y, z + t.z);
	}
	Point operator -(const Point &t) const {
		return Point(x - t.x, y - t.y, z - t.z);
	}
	Point operator /(double t) const {
		return Point(x / t, y / t, z / t);
	}
	double dot(const Point &t) {
		return x * t.x + y * t.y + z * t.z;
	}
	double norm() {
		return this->dot(*this);
	}
	double abs() {
		return SQRT(this->norm());
	}
	Point unit() {
		return *this / abs();
	}
	Point cross(const Point &t) {
		Point ret;
		ret.x = y * t.z - z * t.y;
		ret.y = z * t.x - x * t.z;
		ret.z = x * t.y - y * t.x;
		return ret;
	}
	void read() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
};

double mix(Point a, Point b, Point c) {
	return a.dot(b.cross(c));
}

istream &operator >>(istream &is, Point &t) {
	return is >> t.x >> t.y >> t.z;
}

Point O, A, B, C, D, E, F;
int tests;

int main() {
	cout.setf(ios::fixed);
	cout.precision(10);
	cin >> tests;
	while (tests --) {
		cin >> O >> A >> B >> C >> D >> E >> F;
		A = A - O; B = B - O; C = C - O;
		D = (D - O) * 100; E = (E - O) * 100; F = (F - O) * 100;
		O = O - O;
	}
	return 0;
}

