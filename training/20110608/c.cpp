#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <string>
#include <set>
#include <vector>
using namespace std;

const double eps = 1e-8;
int n, m;
double v[20], a[20], x[20], d[20], q, s;
double ans[20];
vector <double> event;

inline int sgn(const double &a) {
	return a < -eps ? -1 : a > eps ? 1 : 0;
}

bool Less(const double &a, const double &b) {
	return sgn(a - b) == -1;
}

bool Equal(const double &a, const double &b) {
	return sgn(a - b) == 0;
}

void mkevent() {
	event.clear();
	double tmp = 0; event.push_back(tmp);
	for (int i = 0; i < n; ++ i) {
		tmp += v[i] / s;
		event.push_back(tmp);
	}
	for (int i = 0; i < m; ++ i)
		if (sgn(x[i] - tmp) == -1) event.push_back(x[i]);
	sort(event.begin(), event.end(), Less);
	event.erase(unique(event.begin(), event.end(), Equal), event.end());
}

int main () {
	cin >> n >> m >> s;
	for (int i = 0; i < n; ++ i)
		cin >> v[i] >> a[i];
	for (int i = 0; i < m; ++ i)
		cin >> x[i] >> d[i];
	cin >> q;
	while (1) {
		mkevent();
		if (event.size() == 1) break;
		int A = 0, B = -1;
		double speed = 0, height = v[A] / s, curtime = 1e100;
		for (int i = 0; i < (int)event.size() - 1; ++ i) {
			while (Less(height, event[i])) {
				++ A;
				height += v[A] / s;
			}
			double ns = a[A] * (B == -1 ? q : d[B]) + speed;
			curtime = min(curtime, (event[i + 1] - event[i]) * s / ns);
			while (Less(x[B + 1], event[i + 1]) || Equal(x[B + 1], event[i + 1])) {
				++ B;
				speed += ns;
			}
		}
		B = -1; speed = 0, height = 0;
		for (int i = 0; i < n; ++ i) {
			if (sgn(v[i]) == 0) continue;
			double ns = a[A] * (B == -1 ? q : d[B]);
			if (B >= 0) ans[B] += ns * curtime;
			height += v[i] / s;
			v[i] -= ns * curtime;
			while (!Less(v[B + 1], height)) {
				++ B;
				speed += ns;
			}
		}
	}
	return 0;
}

