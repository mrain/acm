#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.);

inline int sgn(double a) {
	return a < -eps ? -1 : a > eps ? 1 : 0;
}

inline double sqr(double a) { return a * a; };

struct point {
	double x, y;
	point(double x = 0, double y = 0)
		: x(x), y(y) {}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
};

struct record {
	int id;
	point p;
	record(int id, point p = point(0, 0))
		: id(id), p(p) {}
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

double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}

double cross(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}

bool parallel(const point &u1, const point &u2, const point &v1, const point &v2) {
	return sgn(cross(u1 - u2, v1 - v2)) == 0;
}

point intersect(const point &u1, const point &u2, const point &v1, const point &v2) {
	double k = cross(u1 - v1, v1 - v2) / cross(u1 - u2, v1 - v2);
	return u1 + (u2 - u1) * k;
}

point a[1010], b[1010], compa, compb;
vector <record> l[1010];
int n, f[1010][1010];

bool cmp(const record &a, const record &b) {
	return dot(a.p - compa, compb - compa) < dot(b.p - compa, compb - compa);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i)
		a[i].read(), b[i].read();
	for (int i = 0; i < n; ++ i)
		for (int j = i + 1; j < n; ++ j)
			if (!parallel(a[i], b[i], a[j], b[j])) {
				point p = intersect(a[i], b[i], a[j], b[j]);
				l[i].push_back(record(j, p));
				l[j].push_back(record(i, p));
			}
	for (int i = 0; i < n; ++ i) {
		compa = a[i]; compb = b[i];
		sort(l[i].begin(), l[i].end(), cmp);
/*
		for (int j = 0; j < (int)l[i].size(); ++ j)
			printf("%d:(%lf,%lf) ", l[i][j].id, l[i][j].p.x, l[i][j].p.y);
		puts("");*/
	}
	memset(f, -1, sizeof(f));
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < (int)l[i].size(); ++ j)
			f[l[i][j].id][i] = j;
	}
/*	
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < n; ++ j) {
			printf("%d ", f[i][j]);
		}
		puts("");
	}
*/
	for (int i = 0; i < n; ++ i) {
		int cnt = 0;
		for (int j = 0; j < n; ++ j) {
			if (i == j || l[j].size() == 0) continue;
			if (f[i][j] == -1) {
				int k = sgn(cross(b[i] - a[i], l[j][0].p - a[i]));
				cnt += k * l[j].size();
			} else {
				int p = f[i][j];
				if (p) {
					int k = sgn(cross(b[i] - a[i], l[j][0].p - a[i]));
					cnt += k * p;
				}
				if (p < (int)l[j].size() - 1) {
					int k = sgn(cross(b[i] - a[i], l[j][p + 1].p - a[i]));
					cnt += k * (l[j].size() - p - 1);
				}
			}
		}
		printf("%d\n", abs(cnt / 2));
	}
	return 0;
}
