#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <complex>
#include <cmath>
using namespace std;

const double pi = acos(-1.);
const double eps = 1e-12;
double u, a, d;

int sgn(double a) {
	return a < -eps ? -1 : a > eps ? 1 : 0;
}

int main() {
	cout.setf(ios::fixed);
	cout.precision(10);
	while (1) {
		cin >> u >> a >> d;
		if (sgn(u) == 0 && sgn(a) == 0 && sgn(d) == d) break;
		a = a * pi / 180;
		double p = sqrt(3) * u;
		double t = (exp(a * u / p) * d - d) / u;
		if (t > 10000. + eps) cout << "God help me!" << endl;
		else {
			int ans = round(t);
			cout << ans << endl;
		}
	}
	return 0;
}

