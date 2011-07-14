#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> PII;
vector <PII> list;
double w[101];
double x, s, r, t;
int n, tests;

int main() {
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		scanf("%lf%lf%lf%lf%d", &x, &s, &r, &t, &n);
		memset(w, 0, sizeof(w));
		w[0] = x;
		for (int i = 0; i < n; ++ i) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			w[c] += b - a;
			w[0] -= b - a;
		}
		double tot = 0.;
		for (int i = 0; i <= 100; ++ i) {
			if ((r + i) * t > w[i]) {
				double tmp = w[i] / (r + i);
				tot += tmp;
				t -= tmp;
			} else {
				tot += t;
				w[i] -= (r + i) * t; t = 0.;
				tot += w[i] / (s + i);
			}
		}
		printf("Case #%d: %.10f\n", ++ ca, tot);
	}
	return 0;
}

