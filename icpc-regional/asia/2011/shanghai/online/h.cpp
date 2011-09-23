#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

long long c[50], m;
int n;

long long gcd(long long a, long long b) {
	return b == 0 ? a : gcd(b, a % b);
}

inline long long lcm(long long a, long long b) {
	return a / gcd(a, b) * b;
}

long long dfs(int d, long long cur) {
	if (cur >= m) return 1ll << ((long long)(n - d + 1));
	if (lcm(cur, c[d]) < m) return 0;
	if (d > n) return 0;
	return dfs(d + 1, cur) + dfs(d + 1, lcm(cur, d));
}

int main() {
	c[40] = 40;
	for (int i = 39; i; -- i)
		c[i] = lcm(i, c[i + 1]);
	int tests, cas = 0;
	cin >> tests;
	while (tests --) {
		cin >> n >> m;
		long long ans = dfs(1, 1);
		if (m == 1) -- ans;
		cout << "Case #" << ++ cas << ": " << ans << endl;
	}
	return 0;
}

