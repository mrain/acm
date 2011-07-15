#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

const double pi = acos(-1.);
const double eps = 1e-8;
const int sp = 1000;
const double step = pi / sp;

inline double sqr(double a) { return a * a; }
inline int sgn(double a) {
	return a < -eps ? -1 : a > eps ? 1 : 0;
}

struct point {
	double x, y;
	point(double x = 0, double y = 0)
		: x(x), y(y) {}
};

inline point polar(const double &a, const double &r) {
	return point(r * cos(a), r * sin(a));
}

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
inline double cross(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}
inline double ang(const point &a) {
	return atan2(a.y, a.x);
}
bool operator <(const point &a, const point &b) {
	if (sgn(a.x - b.x) == 0) return a.y < b.y;
	else return a.x < b.x;
}
inline double len(const point &a) {
	return sqrt(sqr(a.x) + sqr(a.y));
}

struct record {
	int belong;
	double angle;
	point p;
	record(int belong = 0, double angle = 0, point p = point(0, 0))
		: belong(belong), angle(angle), p(p) {}
};
int tests, n, m;
vector <record> p;
point a[100];
record ans[sp * 26 + 1];
double r[100];

inline bool cmp(const record &a, const record &b) {
/*	double a1 = ang(a.p - p[0].p), a2 = ang(b.p - p[0].p);
	if (sgn(a1 - a2) == 0) return len(a.p - p[0].p) < len(b.p - p[0].p);
	else return sgn(a1 - a2) == -1;*/
	return a.p < b.p;
}

void work() {
/*	for (int i = 1; i < (int)p.size(); ++ i)
		if (p[i].p < p[0].p) swap(p[i], p[0]);
	sort(p.begin() + 1, p.end(), cmp);
	ans[m = 1] = p[0];
	for (int i = 1; i < (int)p.size(); ++ i) {
		while (m > 1 && sgn(cross(p[i].p - ans[m - 1].p, ans[m].p - ans[m - 1].p)) > 0)
			-- m;
		ans[++ m] = p[i];
	}
	while (m > 1 && sgn(cross(p[0].p - ans[m - 1].p, ans[m].p - ans[m - 1].p)) > 0)
		-- m;*/
	sort(p.begin(), p.end(), cmp);
	int limit=1;m=0;
	for(int i=0;i<(int)p.size();++i)
	{
		while (m > limit && cross(p[i].p - ans[m - 1].p, ans[m].p - ans[m - 1].p) >= 0)
			-- m;
		ans[++ m] = p[i];
	}
	limit=m;
	for(int i=p.size()-1;i>=0;--i)
	{
		while (m > limit && cross(p[i].p - ans[m - 1].p, ans[m].p - ans[m - 1].p) >= 0)
			-- m;
		ans[++m]=p[i];
	}
	--m;
}

inline double dist(const record &a, const record &b) {
	if (a.belong != b.belong) {
		return len(a.p - b.p);
	} else {
/*		double ang = fabs(a.angle - b.angle);
		if (ang > pi) ang -= pi;*/
		double a1 = a.angle, a2 = b.angle;
		if (a1 < 0) a1 += 2. * pi;
		if (a2 < 0) a2 += 2. * pi;
		double ang = fabs(a1 - a2);
		if (ang > pi) ang = 2 * pi - ang;
		return ang * r[a.belong];
	}
}

double getlen() {
	double ret = 0;
	ans[m + 1] = ans[1];
	for (int i = 1; i <= m; ++ i)
		ret += dist(ans[i], ans[i + 1]);
	return ret;
}

int main() {
	scanf("%d", &tests);
	while (tests --) {
		scanf("%d", &n);
		p.clear();
		for (int i = 0; i < n; ++ i) {
			scanf("%lf%lf%lf", &a[i].x, &a[i].y, &r[i]);
			for (int j = 0; j < sp * 2; ++ j)
				p.push_back(record(i, j * step - pi, a[i] + polar(j * step - pi, r[i])));
		}
		work();
//		cout << m << endl;
//		for (int i = 1; i <= m; ++ i)
//			cout << ans[i].belong << ' ' << ans[i].angle << ' ' <<  ans[i].p.x << ' ' << ans[i].p.y << endl;
		printf("%.10f\n", getlen());
	}
	return 0;
}
