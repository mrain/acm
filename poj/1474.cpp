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

inline double cross(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}

inline double ang(const point &a) {
	return atan2(a.y, a.x);
}

typedef pair<point, point> halfplane;

point intersect(const halfplane &a, const halfplane &b) {
	double k = cross(a.first - b.first, b.first - b.second);
	k /= cross(a.first - a.second, b.first - b.second);
	return a.first + (a.second - a.first) * k;
}

inline bool satisfy(const point &a, const halfplane &b) {
	return sgn(cross(a - b.first, b.second - b.first)) >= 0;
}

ostream &operator <<(ostream &os, const point &a) {
	os << '(' << a.x << ',' << a.y << ')';
	return os;
}

bool cmp(const halfplane &a, const halfplane &b) {
	int res = sgn(ang(a.second - a.first) - ang(b.second - b.first));
	return res == 0 ? satisfy(a.first, b) : res < 0;
}
bool parallel(const halfplane &a, const halfplane &b) {
	return (sgn(cross(a.first - a.second, b.first - b.second)) == 0); 
}

vector <point> halfplaneIntersect(vector <halfplane> v) {
	sort(v.begin(), v.end(), cmp);
	deque<halfplane> q;
	deque<point> ans;
	q.push_back(v[0]);
	for (int i = 1; i < (int)v.size(); ++ i) {
		if (sgn(ang(v[i].second - v[i].first) - ang(v[i - 1].second - v[i - 1].first)) == 0) continue;
		while (ans.size() > 0 && !satisfy(ans.back(), v[i]))
			ans.pop_back(), q.pop_back();
		while (ans.size() > 0 && !satisfy(ans.front(), v[i]))
			ans.pop_front(), q.pop_front();
		if (!parallel(q.back(), q.front()))
			ans.push_back(intersect(q.back(), v[i]));
		q.push_back(v[i]);
	}
	while (ans.size() > 0 && !satisfy(ans.back(), q.front()))
		ans.pop_back(), q.pop_back();
	if (!parallel(q.back(), q.front()))
		ans.push_back(intersect(q.back(), q.front()));
	return vector<point>(ans.begin(), ans.end());
}

point p[2000];
vector <halfplane> hp;
vector <point> res;
int tests, n;

int main() {
	int ca = 0;
	while (scanf("%d", &n), n) {
		for (int i = 0; i < n; ++ i)
			p[i].read();
		p[n] = p[0];
		hp.clear();
		for (int i = 0; i < n; ++ i)
			hp.push_back(halfplane(p[i], p[i + 1]));
		res = halfplaneIntersect(hp);
		printf("Floor #%d\n", ++ ca);
		if (res.size() >= 1) puts("Surveillance is possible.");
		else puts("Surveillance is impossible.");
	}
	return 0;
}
