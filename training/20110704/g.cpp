#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const long long mod = 10000;
long long n;
int p;

inline int regular(long long c) {
	return (c % mod + mod) % mod;
}

inline int add(long long a, long long b) {
	return regular(regular(a) + regular(b));
}

inline int dec(long long a, long long b) {
	return regular(regular(a) - regular(b));
}

inline int mul(long long a, long long b) {
	return regular(regular(a) * regular(b));
}

int power(long long n) {
	int res = 1, tmp = 2;
	while (n) {
		if (n & 1ll) res = mul(res, tmp);
		tmp = mul(tmp, tmp);
		n >>= 1ll;
	}
	return res;
}

int main() {
	int ca = 0;
	while (cin >> n && n) {
		p = power(n - 1);
		int ans = add(mul(p, regular(n)), mul(p, 2));	//'a' and '+'
		ans = add(ans, regular(n) - 2);		//x and it's power
		ans = add(ans, 2 * regular(n) - 2);		//bracket
		long long upper = min(10ll, n + 1), lower = 1;
		for (int i = 1; lower <= n; ++ i, lower = upper, upper = min(upper * 10, n + 1)) {
			ans = add(ans, mul(p, mul(i, regular(upper - lower))));
			ans = add(ans, mul(i, regular(upper - lower)));
		}
		cout << "Case " << ++ ca << ": " << ans << endl;
	}
	return 0;
}
