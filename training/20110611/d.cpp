#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int d, n;
long long ans;

int roundup(int a, int b) {
	return (a / b) + (a % b == 0 ? 0 : 1);
}

int main() {
	while (1) {
		scanf("%d%d", &d, &n);
		if (d == 0 && n == 0) break;
		ans = 0;
		for (int i = 1; i <= n; ++ i) {
			long long k = roundup(d, i);
			if (k * k > d) {
				ans += k;
				//cout << i << ' ' << k << endl;
			}
			else break;
		}
		for (int i = 1; (long long)i * i <= d; ++ i) {
			int a = roundup(d, i), b;
			if (a > n) continue;
			if (i == 1) b = n;
			else b = min(roundup(d, i - 1) - 1, n);
			//cout << "!" << i << ' ' << b << ' ' << a << endl;
			ans += (long long)i * (long long)(b - a + 1);
		}
		cout << ans << endl;
	}
	return 0;
}

