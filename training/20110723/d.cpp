#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
using namespace std;

struct point{
	int x, y;
	point(int x = 0, int y = 0)
		: x(x), y(y) {}
};

int cross(const point &a, const point &b) {
	long long tmp = (long long)a.x * (long long)b.y - (long long)a.y * (long long)b.x;
	return tmp < 0 ? -1 : tmp > 0 ? 1 : 0;
}

bool operator <(const point &a, const point &b) {
	if (a.x == b.x) return a.y < b.y;
	else return a.x < b.x;
}

point operator -(const point &a, const point &b) {
	return point(a.x - b.x, a.y - b.y);
}

point l[100010];
char buf[30];
point s[100010];
int n, m, top;

int main() {
	scanf("%d", &m); n = 0;
	for (int i = 0; i < m; ++ i) {
		point a;
		scanf("%d%d%s", &a.x, &a.y, buf);
//		if (buf[0] == 'Y') l[n ++] = a;
		l[n ++] = a;
	}
	sort(l, l + n);
	int limit = 1;
	top = 0;
	for (int i = 0; i < n; ++ i) {
		while (top > limit && cross(l[i] - s[top - 1], s[top] - s[top - 1]) > 0) -- top;
		s[++ top] = l[i];
	}
	limit = top;
	for (int i = n - 2; i >= 0; -- i) {
		while (top > limit && cross(l[i] - s[top - 1], s[top] - s[top - 1]) > 0) -- top;
		s[++ top] = l[i];
	}
	-- top;
	printf("%d\n", top);
	for (int i = 1; i <= top; ++ i)
		printf("%d %d\n", s[i].x, s[i].y);
	return 0;
}

