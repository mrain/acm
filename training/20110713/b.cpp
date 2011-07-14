#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

vector <double> a, b;
double x[1000], y[1000];
int n;
long long res;

int main() {
	while (scanf("%lf%lf", x + n, y + n) == 2) ++ n;
	res = 0;
	x[n] = x[0]; y[n ++] = y[0];
	for (int i = 0; i < 100000; ++ i) {
		a.clear(), b.clear();
		for (int j = 0; j < n; ++ j) {
			if (y[j] == y[j + 1]) continue;
			double x1 = x[j], x2 = x[j + 1], y1 = y[j], y2 = y[j + 1];
			if (y1 > y2) swap(x1, x2), swap(y1, y2);
			if (i >= y1 && i + 1 <= y2) {
				a.push_back((double)(x2 - x1) / (y2 - y1) * (i - y1) + x1);
				b.push_back((double)(x2 - x1) / (y2 - y1) * (i + 1 - y1) + x1);
			}
		}
		sort(a.begin(), a.end());
		sort(b.begin(), b.end());
		for (int j = 0; j < (int)a.size(); j += 2) {
			double dh = max(a[j], b[j]);
			int t = (int)min(a[j + 1], b[j + 1]);
			int h = (int)dh;
			if (dh > h) ++ h;
			if (t > h) res += t - h;
		}
	}
	cout << res << endl;
	return 0;
}
