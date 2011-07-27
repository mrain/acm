#include <cstdio>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <deque>
#include <cmath>
using namespace std;

const double eps = 1e-8;

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

inline double len(const point &a) {
	return sqrt(dot(a, a));
}

inline double cross(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}

inline double ang(const point &a) {
	return atan2(a.y, a.x);
}

ostream &operator <<(ostream &os, const point &a) {
	os << '(' << a.x << ',' << a.y << ')';
	return os;
}

point intersect(const point &u1, const point &u2, const point &v1, const point &v2) {
	double k = cross(u1 - v1, v1 - v2) / cross(u1 - u2, v1 - v2);
	return u1 + (u2 - u1) * k;
}

bool parallel(const point &u1, const point &u2, const point &v1, const point &v2) {
	return sgn(cross(u1 - u2, v1 - v2)) == 0;
}

point p[2000];
vector <point> res;
int tests, n;

void cut(vector <point> &p, const point &a, const point &b) {
	static vector <point> l;
	l.clear();
	int n = (int)p.size();
	for (int i = 0; i < n; ++ i) {
		if (sgn(cross(p[i] - a, b - a)) > 0)
			l.push_back(p[i]);
		if (sgn(cross(p[i] - a, b - a) * cross(p[(i + 1) % n] - a, b - a)) <= 0 && !parallel(p[i], p[(i + 1) % n], a, b))
			l.push_back(intersect(p[i], p[(i + 1) % n], a, b));
	}
	p.clear();
	for (int i = 0; i < (int)l.size(); ++ i)
		if (!i || sgn(len(l[i] - l[i - 1])) != 0)
			p.push_back(l[i]);
	if (p.size() > 1 && sgn(len(p[0] - p.back())) == 0)
		p.pop_back();
}

int main() {
	int ca = 0;
	while (scanf("%d", &n), n) {
		for (int i = 0; i < n; ++ i)
			p[i].read(), res.push_back(p[i]);
		for (int i = 0; i < n; ++ i) {
			cut(res, p[i], p[(i + 1) % n]);
//			cout << res.size() << endl;
//			for (int i = 0; i < (int)res.size(); ++ i)
//				cout << res[i] << endl;
		}
		if (ca) puts("");
		printf("Floor #%d\n", ++ ca);
		printf("Surveillance is %s.\n", res.size() ? "possible" : "impossible");
	}
	return 0;
}
