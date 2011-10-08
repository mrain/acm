#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const double eps = 1e-7;
const double pi = acos(-1.);
double ans, len, l, b, r, t;

inline int sgn(double a) {
	return a < -eps ? -1 : a > eps ? 1 : 0;
}
inline double sqr(double a) { return a * a; }
inline double dist(double x1, double y1, double x2, double y2) {
	return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}

double calc1() {
//	cout << l << ' ' << r << ' ' << b << ' ' << t << endl;
	if (sgn(sqrt(sqr(b) + sqr(l)) - len) >= 0) return 2 * pi * len;
	double l1 = sqrt(sqr(t) + sqr(l));
	double l2 = sqrt(sqr(b) + sqr(r));
	double a1 = atan2(t, l), a2 = atan2(b, r);
	double ans = pi * 3. / 2. * len;
	double h = t - b, w = r - l, d = sqrt(sqr(h) + sqr(w));

	if (len > l1) ans += (pi / 2 - a1) * len;
	else ans += asin(l / len) * len;
	if (len > l2) ans += a2 * len;
	else ans += asin(b / len) * len;

	l1 = len - l1; l2 = len - l2;
	if (l1 < w && l2 < h) {
		if (l1 > 0) ans += a1 * l1;
		if (l2 > 0) ans += (pi / 2 - a2) * len;
	}

	if (l1 >= w && l2 < h) {
		ans += a1 * l1;
		l1 -= w;
		if (l1 + l2 < h) ans += pi / 2 * l1 + (pi / 2 - a2) * l2;
		else {
			double b1 = acos((sqr(l1) + sqr(h) - sqr(l2)) / (2 * h * l1));
			double b2 = acos((sqr(l2) + sqr(h) - sqr(l1)) / (2 * h * l2));
			ans += (pi / 2 - b1) * l1;
			ans += (pi / 2 - b2) * l2 - a2 * l2;
		}
	}

	if (l1 < w && l2 >= h) {
		ans += (pi / 2 - a2) * l2;
		l2 -= h;
		if (l1 + l2 < w) ans += a1 * l1 + pi / 2 * l2;
		else {
			double b1 = acos((sqr(l1) + sqr(w) - sqr(l2)) / (2 * w * l1));
			double b2 = acos((sqr(l2) + sqr(w) - sqr(l1)) / (2 * w * l2));
			ans += (pi / 2 - b1) * l1 - a1 * l1;
			ans += (pi / 2 - b2) * l2;
		}
	}

	if (l1 >= w && l2 >= w) {
		double b1 = acos((sqr(l1) + sqr(d) - sqr(l2)) / (2 * d * l1));
		double b2 = acos((sqr(l2) + sqr(d) - sqr(l1)) / (2 * d * l2));
		ans += (a1 + asin(h / d) - b1) * l1;
		ans += (pi - asin(h / d) - a2 - b2) * l2;
	}

	return ans;
}

double calc2() {
	if (sgn(len - b) <= 0) return 2 * pi * len;
	double ans = 0;
	ans += pi * len;
	double a1 = atan2(b, l), a2 = atan2(b, r);
	double l1 = len - sqrt(sqr(b) + sqr(l));
	double l2 = len - sqrt(sqr(b) + sqr(r));
	double h = t - b, w = r - l;

	if (sgn(l1) == 1) ans += (pi - a1) * len;
	else ans += (pi / 2 - acos(b / len)) * len;
	if (sgn(l2) == 1) ans += a2 * len;
	else ans += (pi / 2 - acos(b / len)) * len;

	if (sgn(l1) == 1) ans += (a1 - pi / 2) * l1;
	if (sgn(l2) == 1) ans += (pi / 2 - a2) * l2;
	
	l1 -= h; l2 -= h;
	if (l1 + l2 < w + eps) {
		if (l1 > eps) ans += pi / 2 * l1;
		if (l2 > eps) ans += pi / 2 * l2;
	} else {
		double tmp1 = (sqr(l1) + sqr(w) - sqr(l2)) / (2 * w * l1);
		double tmp2 = (sqr(l2) + sqr(w) - sqr(l1)) / (2 * w * l2);
		double b1 = acos(tmp1);
		double b2 = acos(tmp2);
//		printf("%.10f %.10f %.10f %.10f\n", b1, b2, acos(tmp1), acos(tmp2));
//		printf("!!%.10f %.10f %.10f\n", l1, l2, w);
//		printf("!!!%.10f %.10f %.10f %.10f\n", tmp1, b1, tmp2, b2);
		if (pi / 2 - b1 < 0) {
			l1 += h;
			ans -= /*(a1 -*/(pi / 2) * l1;
			double nw = sqrt(sqr(h) + sqr(w));
			b1 = acos((sqr(l1) + sqr(nw) - sqr(l2)) / (2 * nw * l1));
			b2 = acos((sqr(l2) + sqr(nw) - sqr(l1)) / (2 * nw * l2));
			ans += (pi / 2 - b1) * l1; ans += asin(w / nw) * l1;
			ans += (pi / 2 - b2) * l2; ans += asin(h / nw) * l2;
		} else if (pi / 2 - b2 < 0) {
			l2 += h;
			ans -= (pi / 2)/* - a2)*/ * l2;
			double nw = sqrt(sqr(h) + sqr(w));
			b1 = acos((sqr(l1) + sqr(nw) - sqr(l2)) / (2 * nw * l1));
			b2 = acos((sqr(l2) + sqr(nw) - sqr(l1)) / (2 * nw * l2));
			ans += (pi / 2 - b1) * l1; ans += asin(h / nw) * l1;
			ans += (pi / 2 - b2) * l2; ans += asin(w / nw) * l2;
		} else {
			ans += (pi / 2 - b1) * l1;
			ans += (pi / 2 - b2) * l2;
		}
	}

	return ans;
}

int main() {
	while (scanf("%lf%lf%lf%lf%lf", &len, &l, &b, &r, &t) == 5) {
		if (!sgn(len) && !sgn(l) && !sgn(r) && !sgn(b) && !sgn(t)) break;

		if (sgn(b) < 0 && sgn(t) > -1)
			swap(l, b), swap(r, t), swap(b, t);
		if (sgn(b) < 1 && sgn(t) < 1)
			b = -b, t = -t, swap(b, t);
		if (sgn(l) < 1 && sgn(r) < 1)
			l = -l, r = -r, swap(l, r);

		if (sgn(l) == 1) ans = calc1();
		else ans = calc2();
		
		printf("%.8f\n", ans);
	}
	return 0;
}
