#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <cmath>
#include <cctype>
using namespace std;

const double eps = 1e-12;
const double k = sqrt(2);
double r, a, b, c, d;
int state;

double len(double a, double b) {
	return sqrt(a * a + b * b);
}

bool valid(double x, double y) {
	return x * x + y * y <= (r * r) + eps;
}

const char *mark(int a, int b) {
	if (a == 0) return b > 0 ? "north" : "south";
	if (b == 0) return a > 0 ? "east" : "west";
	if (b < 0) {
		if (a < 0) return "southwest";
		else return "southeast";
	} else {
		if (a < 0) return "northwest";
		else return "northeast";
	}
	return "";
}

int sgn(double a) {
	return fabs(a) < eps ? 0 : a < 0 ? -1 : 1;
}

int main() {
	bool first = true;
	while (1) {
		cin >> r;
		if (r < 0) break;
		if (!first) puts("");
		first = false;
		cin >> a >> b >> c >> d;
		if (a == c) {
			printf("%s %.10f\n", b < d ? "north" : "south", fabs(b - d));
			continue;
		}
		if (b == d) {
			printf("%s %.10f\n", a < c ? "east" : "west", fabs(a - c));
			continue;
		}
		if (fabs(a - c) == fabs(b - d)) {
			printf("%s %.10f\n", mark(sgn(c - a), sgn(d - b)), fabs(c - a) * k);
			continue;
		}
		double delta, ans = 1e10, p, px, py;
		int dx = a < c ? 1 : -1, dy = b < d ? 1 : -1;
		// Case 1 (a, b) -> (a, p) -> (c, d)
		delta = fabs(a - c); p = d - dy * delta;
		if (valid(a, p) && fabs(b - p) + delta * k < ans) {
			ans = delta * k + fabs(b - p);
			px = a; py = p;
		}
		// Case 2 (a, b) -> (p, b) -> (c, d)
		delta = fabs(b - d); p = c - dx * delta;
		if (valid(p, b) && delta * k + fabs(a - p) < ans) {
			ans = delta * k + fabs(a - p);
			px = p; py = b;
		}
		// Case 3 (a, b) -> (c, p) -> (c, d)
		delta = fabs(a - c); p = b + dy * delta;
		if (valid(c, p) && delta * k + fabs(d - p) < ans) {
			ans = delta * k + fabs(d - p);
			px = c; py = p;
		}
		// Case 4 (a, b) -> (p, d) -> (c, d)
		delta = fabs(b - d); p = a + dx * delta;
		if (valid(p, d) && delta * k + fabs(a - p) < ans) {
			ans = delta * k + fabs(a - p);
			px = p; py = d;
		}
		printf("%s %.10f\n", mark(sgn(px - a), sgn(py - b)), len(a - px, b - py));
		printf("%s %.10f\n", mark(sgn(c - px), sgn(d - py)), len(c - px, d - py));
	}
	return 0;
}

