#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const double eps = 1e-8;
const double pi = acos(-1.);
struct line { double a, b, c; };

int cmp(double x) {
	return x < -eps ? -1 : x > eps ? 1 : 0;
}
class point {
	public:
		double x, y;
		point(double x = 0, double y = 0) : x(x), y(y) {}
		void input() { scanf("%lf%lf", &x, &y); }
		void output() { printf("%.3f %.3f\n", x, y); }
		point operator -(const point &a) const {
			return point(x - a.x, y - a.y);
		}
		point operator +(const point &a) const {
			return point(x + a.x, y + a.y);
		}
		point operator *(const double &a) const {
			return point(x * a, y * a);
		}
		double operator *(const point &a) const {
			return x * a.y - y * a.x;
		}
		point operator /(const double &a) const {
			return point(x / a, y / a);
		}
		double operator ^(const point &a) const {
			return x * a.x + y * a.y;
		}
		bool operator ==(const point &a) const {
			return cmp(x - a.x) == 0 && cmp(y - a.y) == 0;
		}
};

double dis(const point &a) { return sqrt(a.x*a.x + a.y*a.y); }
double dis(const point &a, const point &b) { return dis(b-a); }

double dis_point_segment(point p, point s, point t) {
	if (((p-t)^(s-t))>0 && (((p-s)^(t-s))>0)) return fabs((p-s)*(t-s))/dis(s-t);
	else return min(dis(p-s), dis(p-t));
}

point rotate_point(const point &a, double p) {
	return point(
		a.x * cos(p) - a.y * sin(p),
		a.x * sin(p) + a.y * cos(p)
	);
}

line point_make_line(const point &a, const point &b) {
	line h;
	h.a = b.y - a.y;
	h.b = -(b.x - a.x);
	h.c = -a.x*b.y + a.y*b.x;
	return h;
}

point line_make_point(line a, line b) {
	point h;
	h.y = -(a.c * b.a - b.c * a.a) / (a.b * b.a - b.b * a.a);
	if (fabs(a.a) < eps) h.x = (-b.c - h.y * b.b) / b.a;
	else h.x = (-a.c - h.y * a.b) / a.a;
	return h;
}

double dot(point a, point b, point c) {
	return (b - a) ^ (c - a);
}

double area(point a, point b, point c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool PointOnSegment(point p, point s, point t) {
	return cmp(area(p, s, t)) == 0 && cmp(dot(p, s, t)) <= 0;
}

int PointInPolygon(point cp, point a[], int n) {
	int k, d1, d2, wn = 0;
	for (int i = 0; i < n; ++ i) {
		if ( PointOnSegment(cp, a[i], a[i + 1])) return 2;
		k = cmp(area(a[i], a[i + 1], cp));
		d1 = cmp(a[i].y - cp.y);
		d2 = cmp(a[i + 1].y - cp.y);
		if (k > 0 && d1 <= 0 && d2 > 0) wn ++;
		if (k < 0 && d2 <= 0 && d1 > 0) wn --;
	}
	return wn != 0;
}

bool parallel(line a, line b) {
	if (cmp(a.b*b.a - b.b*a.a) == 0) return true;
	return false;
}

point plg[102];
int n;
double r;
vector <point> l;

bool valid(const point &p) {
	if (!PointInPolygon(p, plg, n)) return false;
	for (int i = 0; i < n; ++ i)
		if (cmp(dis_point_segment(p, plg[i], plg[i + 1]) - r) == -1)
			return false;
	return true;
}

int main() {
	scanf("%d%lf", &n, &r);
	for (int i = 0; i < n; ++ i)
		plg[i].input();
//	reverse(plg, plg + n);
	plg[n] = plg[0]; plg[n + 1] = plg[1];
	/*for (int i = 0; i < n; ++ i) {
		point a = plg[i + 1] - plg[i], b = plg[i + 2] - plg[i + 1];
		if (cmp(a * b) != 1) continue;
		double theta = asin(a * b / dis(a) / dis(b));
		if (cmp(a ^ b) > 0) theta = pi - theta;
		//cout << theta / pi * 180 << endl;
		point p = rotate_point(b, theta / 2);
		p = p / dis(p);
		p = plg[i + 1] + (p * (r / sin(theta / 2)));
		p.output();
		if (valid(p)) l.push_back(p);
	}*/
	for (int i = 0; i < n; ++ i)
		for (int j = i + 1; j < n; ++ j) {
			line A = point_make_line(plg[i + 1], plg[i]);
			line B = point_make_line(plg[j + 1], plg[j]);
			if (parallel(A, B)) continue;
			point c = line_make_point(A, B);
			point ta = plg[i] - c, tb = plg[j] - c;
			if (ta == point(0, 0)) ta = plg[i + 1] - c;
			if (tb == point(0, 0)) tb = plg[j + 1] - c;
			if (cmp(ta * tb) != 1) swap(ta, tb);
			double theta = asin(ta * tb / dis(ta) / dis(tb));
			if (cmp(ta ^ tb) > 0) theta = pi - theta;
			double len1 = r / sin(theta / 2), len2 = r / cos(theta / 2);
			point p = rotate_point(tb, theta / 2);
			if (cmp(len1) == 0 || cmp(len2) == 0) continue;
			p = p / dis(p) * len1;
			if (valid(p + c)) l.push_back(p + c);
			if (valid(c - p)) l.push_back(c - p);
			p = rotate_point(p, pi / 2);
			p = p / len1 * len2;
			if (valid(p + c)) l.push_back(p + c);
			if (valid(c - p)) l.push_back(c - p);
		}
	double maxd = -1e100;
	for (int i = 0; i < (int)l.size(); ++ i) {
		for (int j = i + 1; j < (int)l.size(); ++ j)
			maxd = max(maxd, dis(l[i], l[j]));
	}
	//cout << maxd << endl;
	for (int i = 0; i < (int)l.size(); ++ i)
		for (int j = i + 1; j < (int)l.size(); ++ j)
			if (cmp(dis(l[i], l[j]) - maxd) == 0) {
				printf("%.4f %.4f %.4f %.4f\n", l[i].x, l[i].y, l[j].x, l[j].y);
				return 0;
			}
	return 0;
}
