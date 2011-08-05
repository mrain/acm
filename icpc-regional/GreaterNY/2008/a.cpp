#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int main() {
	int a, b, tests;
	int ca = 0;
	cin >> tests;
	while (tests --) {
		cin >> a >> b;
		int k = gcd(a, b);
		cout << ++ ca << ' ' << a * b / k << ' ' << k << endl;
	}
	return 0;
}
