#include <cstdio>
#include <algorithm>
#include <map>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <set>
using namespace std;

struct point{
	int a, b, c;
	point(int a = 0, int b = 0, int c = 0)
		: a(a), b(b), c(c) {}
	void read() {
		static char buf[300];
		scanf("%s", buf);
		int l = strlen(buf);
		for (int i = 0; i < l; ++ i)
			if (buf[i] == ',') buf[i] = ' ';
		istringstream is(buf);
		is >> a >> b >> c;
	}
	bool operator <(const point &t) const {
		if (a == t.a) {
			if (b == t.b) return c < t.c;
			else return b < t.b;
		} else return a < t.a;
	}
};

set<point> h;
int tests, n, ans;
point p[101];

bool check(point a) {
	if (h.count(a)) {
		ans -= 2;
		return true;
	}
	return false;
}

int main() {
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		h.clear();
		scanf("%d", &n);
		for (int i = 0; i < n; ++ i)
			p[i].read();
		ans = 6;
		int err = -1;
		h.insert(p[0]);
		for (int i = 1; i < n; ++ i) {
			bool flag = false;
			ans += 6;
			flag |= check(point(p[i].a - 1, p[i].b, p[i].c));
			flag |= check(point(p[i].a + 1, p[i].b, p[i].c));
			flag |= check(point(p[i].a, p[i].b - 1, p[i].c));
			flag |= check(point(p[i].a, p[i].b + 1, p[i].c));
			flag |= check(point(p[i].a, p[i].b, p[i].c - 1));
			flag |= check(point(p[i].a, p[i].b, p[i].c + 1));
			if (!flag || h.count(p[i])) {
				err = i;
				break;
			}
			h.insert(p[i]);
		}
		printf("%d ", ++ ca);
		if (err != -1) printf("NO %d\n", err + 1);
		else printf("%d\n", ans);
	}
	return 0;
}

