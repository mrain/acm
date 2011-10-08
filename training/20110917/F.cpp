#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int W, H, a,b;
double X1, Y1, X2, Y2;
int t1, t2;

const double eps = 1e-9;

bool inside(double X, double Y, int T) {
	double A = (double)a * 0.5, B = (double)b * 0.5;
	if (T == 2) swap(A, B);
	
	return  X - A >= -1e-8 && X + A <= W + 1e-8 && Y - B >= -1e-8 && Y + B <= H + 1e-8;
}

double dist(double x, double y) {
	return sqrt(x * x + y * y);
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
