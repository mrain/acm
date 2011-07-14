#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;
const double eps = 1e-8;

struct Point {
	double x, y;
	Point(double x = 0, double y = 0) : x(x), y(y) {}
};
Point operator +(const Point &a, const Point &b) {
	return Point(a.x + b.x, a.y + b.y);
}
Point operator -(const Point &a, const Point &b) {
	return Point(a.x - b.x, a.y - b.y);
}
Point operator *(const Point &a, double b) {
	return Point(a.x * b, a.y * b);
}

char a[20][20];
int r, c, d;
int tests;

int main() {
	int ca = 0;
	scanf("%d", &tests);
	while (tests --) {
		scanf("%d%d%d", &r, &c, &d);
		for (int i = 0; i < r; ++ i) {
			scanf("%s", a[i]);
			for (int j = 0; j < c; ++ j)
				a[i][j] -= '0';
		}
		bool find = false;
		int ans = -1;
		for (int i = r; i >= 3 && !find; -- i)
			for (int j = 0; j < r - i + 1 && !find; ++ j)
				for (int k = 0; k < c - i + 1 && !find; ++ k) {
					Point center(j + i / 2. - 0.5, k + i / 2. - 0.5), Sum(0, 0);
					for (int p = 0; p < i; ++ p)
						for (int q = 0; q < i; ++ q) {
							if (!p && !q || !p && q == i - 1 || p == i - 1 && !q || p == i - 1 && q == i - 1) continue;
							int x = j + p, y = k + q;
							Point tmp = (Point(x, y) - center) * a[x][y];
							Sum = Sum + tmp;
						}
					if (fabs(Sum.x) < eps && fabs(Sum.y) < eps) {
						ans = i;
						find = true;
						break;
					}
				}
		printf("Case #%d: ", ++ ca);
		if (ans == -1) puts("IMPOSSIBLE");
		else printf("%d\n", ans);
	}
	return 0;
}

