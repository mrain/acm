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
	if (a.second >= 0 && b.second >= 0) {
		if (a.second == 0 && b.second == 0) {
			if (a.first > 0 && b.first > 0) return a.first > b.first;
			if (a.first < 0 && b.first < 0) return a.first > b.first;
			return a.first > 0;
		}
		if (a.second == 0) return a.first > 0;
		if (b.second == 0) return b.first < 0;
		if (cross(a, b) == 0) return a.first > b.first;
		else return cross(a, b) >= 0;
	} else if (a.second < 0 && b.second < 0) {
		if (cross(a, b) == 0) return a.first > b.first;
		else return cross(a, b) >= 0;
	} else return a.second > b.second;
}

int calc(vector<point> &l) {
	if (l.size() < 3) return 0;
	sort(l.begin(), l.end(), cmp);

	int n = l.size(), ret = n, p = 0, q = 1;

/*	for (int i = 0; i < n; ++ i)
		cout << l[i].first << ' ' << l[i].second << endl;
	cout << endl;*/

	for (int i = 0; i < n; ++ i) {
		while (q != i && cross(l[i], l[q]) >= 0) {
			q = (q + 1) % n;
		}
		while ((p + 1) % n != i && cross(l[i], l[(p + 1) % n]) > 0) {
			p = (p + 1) % n;
		}
		//cout << i << ' ' <<  p << ' ' << q << ' ' << cross(l[i], l[p]) << ' ' << cross(l[i], l[q]) << endl;
		ret = min(ret, min((p + n - i) % n, (i + n - q) % n));
	}
	return ret;
}

int main() {
	cin >> T;
	for (int t = 1; t <= T; ++ t) {
		cin >> n;
		for (int i = 0; i < n; ++ i) {
			cin >> a[i].first >> a[i].second;
			ans[i] = n + 1;
		}
		for (int i = 0; i < n; ++ i) {
			l.clear();
			for (int j = 0; j <n; ++ j)
				if (i != j) l.push_back(a[j] - a[i]);
			ans[i] = calc(l);
		}
		printf("Case #%d:\n", t);
		for (int i = 0; i < n; ++ i)
			printf("%d\n", ans[i]);
	}
    return 0;
}
