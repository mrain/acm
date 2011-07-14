#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

int days[13] = {
	0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

struct date{
	int d, m, y;
	date(int d = 0, int m = 0, int y = 0)
		: d(d), m(m), y(y) {}
	void read() {
		scanf("%d%d%d", &d, &m, &y);
	}
	void operator ++() {
		++ d;
		int p = days[m];
		if ((y % 100 != 0 && y % 4 == 0) || (y % 400) == 0)
			if (m == 2) ++ p;
		if (d > p) {
			++ m; d = 1;
			if (m > 12) ++ y, m = 1;
		}
	}
	bool operator ==(const date &b) const {
		return y == b.y && m == b.m && d == b.d;
	}
};

date d[2000];
int c[2000], ans, tot, n;

int delta(date a, date b) {
	int ret = 0;
	while (!(a == b)) ++ a, ++ ret;
	return ret;
}

int main() {
	while (scanf("%d", &n), n) {
		ans = tot = 0;
		for (int i = 0; i < n; ++ i) {
			d[i].read(); scanf("%d", &c[i]);
			if (i) {
				int tmp = delta(d[i - 1], d[i]);
				if (tmp == 1 || c[i] == c[i - 1]) {
//					cout << i << endl;
					ans += tmp;
					tot += c[i] - c[i - 1];
				}
			}
		}
		cout << ans << ' ' << tot << endl;
	}
	return 0;
}
