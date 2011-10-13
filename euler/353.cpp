#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int n;

int mysqrt(int a) {
	return (int)(sqrt(a) + 1e-6);
}

void work(int n) {
	int cnt = 0;
	for (int a = 0; a <= n; ++ a)
		for (int b = 0; b <= n; ++ b) {
			int c2 = n * n - a * a - b * b, c = mysqrt(c2);
			if (c * c == c2) {
				++ cnt;
//				cout << a << ' ' << b << ' ' << c << endl;
//				if (c) cout << a << ' ' << b << ' ' << -c << endl;
			}
		}
	cout << cnt << endl;
}

int main() {
	int n;
	while (cin >> n) work(n);
	return 0;
}

