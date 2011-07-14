#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int M, Y, tests;
double p, q, ans, a, b, s, t, k1, k2;

void dfs1(int c, int d, double g) {
	if (c == 4) {
		s += g;
		return;
	}
	if (d == 4) return;
	if (c == 3 && d == 3) {
		s += g * p * q / (1 - k1);
		return;
	}
	double x = p;
	if (((c + d) & 1) == 1) x = q;
	dfs1(c + 1, d, g * x);
	dfs1(c, d + 1, g * (1 - x));
}
void dfs2(int c, int d, double g) {
	if (c == 4) {
		t += g;
		return;
	}
	if (d == 4) return;
	if (c == 3 && d == 3) {
		t += g * p * q / (1 - k1);
		return;
	}
	double x = p;
	if (((c + d) & 1) == 0) x = q;
	dfs2(c + 1, d, g * x);
	dfs2(c, d + 1, g * (1 - x));
}
void dfs3(int c, int d, double g) {
	if (c == 6) {
		a += g;
		return;
	}
	if (d == 6) return;
	if (c == 5 && d == 5) {
		a += g * s * t / (1 - k2);
		return;
	}
	double x = s;
	if (((c + d) & 1) == 1) x = t;
	dfs3(c + 1, d, g * x);
	dfs3(c, d + 1, g * (1 - x));
}
void dfs4(int c, int d, double g) {
	if (c == 6) {
		b += g;
		return;
	}
	if (d == 6) return;
	if (c == 5 && d == 5) {
		b += g * s * t / (1 - k2);
		return;
	}
	double x = s;
	if (((c + d) & 1) == 0) x = t;
	dfs4(c + 1, d, g * x);
	dfs4(c, d + 1, g * (1 - x));
}
void dfs5(int c, int d, double g) {
	if (c == 3) {
		ans += g;
		return;
	}
	if (d == 3) return;
	double x = a;
	if (((c + d) & 1) == 1) x = b;
	dfs5(c + 1, d, g * x);
	dfs5(c, d + 1, g * (1 - x));
}

int main() {
	freopen("e.in", "r", stdin);
	scanf("%d", &tests);
	int ca = 0;
	cout.setf(ios::fixed);
	cout.precision(4);
	while (tests --) {
		ans = p = q = s = t = a = b = 0;
		scanf("%d%d", &M, &Y);
		p = (double)M / 100.;
		q = (double)Y / 100.;
		k1 = (1 - p) * q + (1 - q) * p;
		dfs1(0, 0, 1.);
		dfs2(0, 0, 1.);
		k2 = (1 - s) * t + (1 - t) * s;
		dfs3(0, 0, 1.);
		dfs4(0, 0, 1.);
		dfs5(0, 0, 1.);
		cout << "Case #" << ++ ca << ": " << ans * 100 << '\%' << endl;
	}
	return 0;
}

