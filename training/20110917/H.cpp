#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

struct point{
	double x, y;
	point(double x = 0, double y = 0)
		: x(x), y(y) {}
};

point operator -(const point &a, const point &b) {
	return point(a.x - b.x, a.y - b.y);
}

double cross(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}

double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}

int W, H, a,b;
double X1, Y1, X2, Y2;
int t1, t2;

const double eps = 1e-9;

int sgn(double a) {
	return a < -eps ? -1 : a > eps ? 1 : 0;
}

bool inside(double X, double Y, int T) {
	double A = (double)a * 0.5, B = (double)b * 0.5;
	if (T == 2) swap(A, B);
	
	return  X - A >= -1e-8 && X + A <= W + 1e-8 && Y - B >= -1e-8 && Y + B <= H + 1e-8;
}

double dist(double x, double y) {
	return sqrt(x * x + y * y);
}


bool is_intersect(const point &u1, const point &u2, const point &v1, const point &v2) {
	return sgn(cross(v1 - u2, u1 - u2) * cross(v2 - u2, u1 - u2)) < 0
		&& sgn(cross(u1 - v2, v1 - v2) * cross(u2 - v2, v1 - v2)) < 0;
}

bool same_side(const point &a, const point &b, const point &u1, const point &u2) {
	return sgn(cross(a - u1, u1 - u2) * cross(b - u1, u1 - u2)) >= 0;
}

double work(const point &s, const point &e, const point &a, const point &b) {
	if (same_side(s, e, a, b)) {
		if (a.x == b.x) {
			point p(2 * a.x - s.x, s.y);
			return is_intersect(p, e, a, b) ? sqrt(dot(p - e, p - e)) : 1e100;
		} else {
			point p(s.x, 2 * a.y - s.y);
			return is_intersect(p, e, a, b) ? sqrt(dot(p - e, p - e)) : 1e100;
		}
	} else {
		return is_intersect(s, e, a, b) ? sqrt(dot(s - e, s - e)) : 1e100;
	}
}

double dist(const point &a, const point &b) {
	return sqrt(dot(a-b,a-b));
}

double calc() {
	//if (a * a + b * b > H * H || a * a + b * b > W * W) return -1;
	double d = sqrt((double)a * a + b * b) * 0.5;
//	double d = max(a, b) * 0.5;
	double ax = d, bx = (double)W - d;
	double ay = d, by = (double)H - d;
	
	if (ax > bx + 1e-8 || ay > by + 1e-8) return -1;
	
	double X3 = X1, Y3 = Y1;
	
	double ret = 0.;
	if (X1 < ax) X3 = ax;
	if (X1 > bx) X3 = bx;
	if (Y1 < ay) Y3 = ay;
	if (Y1 > by) Y3 = by;
	
	//ret += fabs(X1 - X2) + fabs(Y1 - Y2);
	ret = dist(X3 - X1, Y3 - Y1) + dist(X3 - X2, Y3 - Y2);

	point bl(ax, ay), tl(ax, by), br(bx, ay), tr(bx, by);
	point s(X1, Y1), e(X2, Y2);
	if (X1 > ax - eps && X1 < bx + eps && Y1 > ay - eps && Y1 < by + eps) return sqrt(dot(s - e, s - e));
	if (X2 > ax - eps && X2 < bx + eps && Y2 > ay - eps && Y2 < by + eps) return sqrt(dot(s - e, s - e));

	ret = min(ret, dist(s, bl) + dist(bl, e));
	ret = min(ret, dist(s, br) + dist(br, e));
	ret = min(ret, dist(s, tl) + dist(tl, e));
	ret = min(ret, dist(s, tr) + dist(tr, e));

	ret = min(ret, work(s, e, bl, tl));
	ret = min(ret, work(s, e, tl, tr));
	ret = min(ret, work(s, e, tr, br));
	ret = min(ret, work(s, e, br, bl));

	return ret;
}

int main() {

	while (scanf("%d%d%d%d", &W, &H, &a, &b) == 4) {
		scanf("%lf%lf%d%lf%lf%d", &X1, &Y1, &t1, &X2, &Y2, &t2);
		
		if (!inside(X1, Y1, t1) || !inside(X2, Y2, t2)) {
			puts("-1"); continue;
		}
		
		if (t1 == t2) {
			printf("%.3f\n", dist(X1 - X2, Y1 - Y2)); continue;	
		}
		
		double ans = calc();
		if (ans < 0.) puts("-1");
		else printf("%.3f\n", ans);
	}
	
	return 0;
}
