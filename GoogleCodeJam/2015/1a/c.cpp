#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <stack>
using namespace std;

typedef pair<long long, long long> point;

point a[10010], p;
vector<point> l;
int n, T, ans[10010];

point operator -(const point &a, const point &b) {
	return make_pair(a.first - b.first, a.second - b.second);
}

long long cross(const point &a, const point &b) {
	return a.first * b.second - a.second * b.first;
}

long long dot(const point &a, const point &b) {
	return a.first * b.first + a.second * b.second;
}

bool cmp(const point &a, const point &b) {
	long long k = cross(a - p, b - p);
	if (k == 0) return (dot(a - p, a - p) > dot(b - p, b - p));
	else return k > 0;
}

bool check(const point &a, const vector<point> &l) {
	for (int i = 0; i < (int)l.size(); ++ i)
		if (a == l[i]) return true;
	for (int i = 0; i < (int)l.size() - 1; ++ i) {
		point p = l[i], q = l[i + 1];
		if (cross(p - a, q - a) == 0)
			return true;
	}
	return false;
}

int bitcount(int x) {
	return x == 0 ? 0 : bitcount(x - (x & (-x))) + 1;
}

void convex_hull(vector<point> &l) {
	int n = l.size();
	if (n < 2) return;
	for (int i = 1; i < n; ++ i)
		if (l[i].second < l[0].second || (l[i].second == l[0].second && l[i].first < l[0].first))
			swap(l[0], l[i]);
	p = l[0];
	sort(l.begin() + 1, l.end(), cmp);

	int s[100], ss;
	ss = 2; s[0] = 0; s[1] = 1;
	for (int i = 2; i < n; ++ i) {
		while (ss > 1 && cross(l[i] - l[s[ss - 2]], l[s[ss - 1]] - l[s[ss - 2]]) > 0)
			-- ss;
		s[ss ++] = i;
	}
	while (ss > 1 && cross(l[0] - l[s[ss - 2]], l[s[ss - 1]] - l[s[ss - 2]]) > 0)
		-- ss;
	for (int i = 0; i < ss; ++ i) {
		l[i] = l[s[i]];
	}
	l.resize(ss);
}

int main() {
	cin >> T;
	for (int t = 1; t <= T; ++ t) {
		cin >> n;
		for (int i = 0; i < n; ++ i) {
			cin >> a[i].first >> a[i].second;
			ans[i] = n - 1;
		}
		for (int mask = 0; mask < (1 << n); ++ mask) {
		//for (int mask = (1 << n) - 1; mask < (1 << n); ++ mask) {
			l.clear();
			for (int i = 0; i < n; ++ i)
				if (mask & (1 << i))
					l.push_back(a[i]);
			convex_hull(l);
/*
			if (mask == (1 << n) - 1) {
				for (int i = 0; i < (int)(l.size()); ++ i)
					cout << l[i].first << ' ' << l[i].second << endl;
			}*/

			int k = n - bitcount(mask);
			for (int i = 0; i < n; ++ i)
				if ((mask & (1 << i))) {
					if (check(a[i], l))
						ans[i] = min(k, ans[i]);
				}
		}
		printf("Case #%d:\n", t);
		for (int i = 0; i < n; ++ i)
			printf("%d\n", ans[i]);
	}
    return 0;
}
