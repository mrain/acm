#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <complex>
using namespace std;

complex<double> A, B, C, a, b, c;
int tests;

int main() {
	cout.setf(ios::fixed);
	cout.precision(2);
	cin >> tests;
	int ca = 0;
	while (tests --) {
		double x1, y1, x2, y2, x3, y3;
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
		a = complex<double>(x1, y1);
		b = complex<double>(x2, y2);
		c = complex<double>(x3, y3);
		A = complex<double>(3, 0);
		B = (a + b + c) * -2.;
		C = a * b + b * c + a * c;
		complex<double> p = (-B + sqrt(B * B - 4. * A * C)) / 2. / A;
		complex<double> q = (-B - sqrt(B * B - 4. * A * C)) / 2. / A;
		if (p.imag() > q.imag()) swap(p, q);
		if (p.real() > q.real()) swap(p, q);
		complex<double> mid = (a + b) / 2.;
		cout << ++ ca << ' ' << p.real() << ' ' << p.imag() << ' ' << q.real() << ' ' << q.imag() << ' ' << abs(p - mid) + abs(q - mid) << endl;
	}
	return 0;
}
