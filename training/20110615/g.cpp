#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int n;
double fact[6000], a[6000];

int main() {
	fact[0] = 1;
	for (int i = 1; i < 600; ++ i) {
		fact[i] = i * fact[i - 1];
	}
	a[1] = 1; a[0] = 1;
	for (int i = 2; i < 600; ++ i) {
		a[i] = 0;
		for (int k = 1; k <= i; ++ k)
			a[i] += a[i - k] / fact[i - k] * fact[i - 1] / fact[k - 1];
	}
	while (1) {
		cin >> n;
		if (!n) return 0;
		printf("%d %.0f\n", n, a[n]);
	}
//a(n) = (n-1)! sum_{k=1}^{n} a(n-k)/((n-k)! (k-1)!)
	return 0;
}

