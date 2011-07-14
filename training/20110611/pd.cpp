#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int d, n;
long long ans;

int main() {
	while (1) {
		scanf("%d%d", &d, &n);
		if (d == 0 && n == 0) break;
		ans = 0;
		for (int i = 1; i <= n; ++ i) {
			long long k = (long long)(d / i) + (d % i == 0 ? 0 : 1);
			ans += k;
			cout << i << ' ' << k << endl;
		}
		cout << ans << endl;
	}
	return 0;
}

