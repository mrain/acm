#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.);

inline int sgn(double a) { return a < -eps ? -1 : a > eps ? 1 : 0; }
inline double sqr(double a) { return a * a; }
inline double mysqrt(double a) { return sqrt(max(a, 0.)); }

typedef pair<double, double> PD;
struct point {
	double x, y;
	point(double x = 0, double y = 0)
		: x(x), y(y) {}
};

inline point operator +(const point &a, const point &b) {
	return point(a.x + b.x, a.y + b.y);
}
inline point operator -(const point &a, const point &b) {
	return point(a.x - b.x, a.y - b.y);
}
inline point operator *(const point &a, const double &b) {
	return point(a.x * b, a.y * b);
}
inline double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}
inline double cross(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}
inline double norm(const point &a) { return dot(a, a); }
inline double len(const point &a) { return mysqrt(norm(a)); }
inline double ang(const point &a) { return atan2(a.y, a.x); }
inline point unit(const point &a) { return a * (1. / len(a)); }

int tests, n;
point c[30];
double r[30], dist[2010];
bool inq[2010];
vector <point> a;
vector <int> e[2010];
queue <int> q;

void make_event(int i, int j) {
	double dis = len(c[i] - c[j]);
	if (sgn(dis) == 0) return;
	if (r[i] + r[j] < dis - eps || fabs(r[i] - r[j]) > dis + eps) return;
	point d = unit(c[j] - c[i]), h = point(-d.y, d.x);
	if (sgn(r[i] + r[j] - dis) == 0 || sgn(fabs(r[i] - r[j]) - dis) == 0) {
		a.push_back(c[i] + d * r[i]);
		return;
	}
	double l1 = (sqr(r[i]) + sqr(dis) - sqr(r[j])) / (2 * dis);
	double h1 = mysqrt(sqr(r[i]) - sqr(l1));
	a.push_back(c[i] + d * l1 + h * h1);
	a.push_back(c[i] + d * l1 - h * h1);
}

bool check(const point &p, const point &q) {
	if (len(p - q) < eps) return true;
	static vector <PD> h;
	h.clear();
	double l = len(p - q);
	for (int i = 0; i < n; ++ i) {
		double l1 = dot(c[i] - p, q - p) / l;
		double h1 = mysqrt(norm(c[i] - p) - sqr(l1));
		if (h1 > r[i] + eps) continue;
		double delta = mysqrt(sqr(r[i]) - sqr(h1));
		h.push_back(make_pair(l1 - delta - eps, l1 + delta + eps));
	}
	sort(h.begin(), h.end());
	double last = 0;
	for (int i = 0; i < (int)h.size(); ++ i)
		if (h[i].first > last) break;
		else last = max(last, h[i].second);
	return last - l > -eps;
}

int main() {
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		scanf("%d", &n);
		a.clear();
		for (int i = 0; i < n; ++ i)
			scanf("%lf%lf%lf", &c[i].x, &c[i].y, &r[i]);
		a.push_back(c[0]); a.push_back(c[n - 1]);
		for (int i = 0; i < n; ++ i)
			for (int j = i + 1; j < n; ++ j)
				make_event(i, j);
		for (int i = 0; i < (int)a.size(); ++ i)
			e[i].clear();
		for (int i = 0; i < (int)a.size(); ++ i)
			for (int j = i + 1; j < (int)a.size(); ++ j)
				if (check(a[i], a[j])) {
//					printf("(%.4f, %.4f) -> (%.4f, %.4f) : %.4f\n", a[i].x, a[i].y, a[j].x, a[j].y, len(a[i] - a[j]));
					e[i].push_back(j), e[j].push_back(i);
				}

		while (!q.empty()) q.pop();
		for (int i = 0; i < (int)a.size(); ++ i) dist[i] = 1e20;
		dist[0] = 0.; q.push(0); inq[0] = true;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			inq[u] = false;
			for (int i = 0; i < (int)e[u].size(); ++ i) {
				int v = e[u][i];
				if (dist[v] > dist[u] + len(a[u] - a[v]) + eps) {
					dist[v] = dist[u] + len(a[u] - a[v]);
					if (!inq[v]) q.push(v), inq[v] = true;
				}
			}
		}
		printf("Case %d: ", ++ ca);
		if (dist[1] >= 1e10) puts("No such path.");
		else printf("%.4f\n", dist[1]);
	}
	return 0;
}
