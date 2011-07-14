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

int n;
double a[1000], tot, delta, upper, lower;
double l[1000], now;
int p[1000];
bool chose[1000];

bool dfs(int dep) {
	if (dep == n) {
		bool first = true;
		for (int i = 0; i < n; ++ i)
			if (chose[i]) {
				if (!first) putchar(' ');
				first = false;
				printf("%d", i + 1);
			}
		puts("");
		return true;
	}
	if (now + l[dep + 1] > lower) {
		if (dfs(dep + 1)) return true;
	}
	now += a[p[dep]];
	chose[p[dep]] = true;
	if (now < upper) {
		if (now > lower) {
			bool first = true;
			for (int i = 0; i < n; ++ i)
				if (chose[i]) {
					if (!first) putchar(' ');
					first = false;
					printf("%d", i + 1);
				}
			puts("");
			return true;
		}
		if (dfs(dep + 1)) return true;
	}
	chose[p[dep]] = false;
	now -= a[p[dep]];
	return false;
}

bool cmp(const int &x, const int &y) {
	return a[x] < a[y];
}

int main() {
	while (1) {
		tot = 0.;
		scanf("%d", &n);
		if (!n) break;
		for (int i = 0; i < n; ++ i) {
			scanf("%lf", &a[i]);
			tot += a[i];
			p[i] = i;
		}
		sort(p, p + n, cmp);
//		reverse(p, p + n);
		lower = tot / 2.019; upper = tot / 1.981;
		l[n] = 0; now = 0.;
		for (int i = n - 1; i >= 0; -- i) l[i] = l[i + 1] + a[p[i]];
		memset(chose, 0, sizeof(chose));
		if (!dfs(0)) return 1/0;
	}
	return 0;
}

