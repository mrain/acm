#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int limit = 20000000;
int tests, primecount;
int prime[limit + 10];
bool notprime[limit + 10];
long long n;

void init() {
	primecount = 0;
	for (int i = 2; i < limit; ++ i) {
		if (!notprime[i]) prime[primecount ++] = i;
		for (int j = 0; j < primecount; ++ j) {
			if ((long long)i * prime[j] >= limit) break;
			notprime[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}

int main() {
	cin >> tests;
	init();
	for (int testcase = 1; testcase <= tests; ++ testcase) {
		cin >> n;
		long long ans = 0;
		for (int i = 0; (long long)prime[i] * prime[i] <= n; ++ i) {
			long long tmp = prime[i]; int cnt = 0;
			while (tmp <= n) {
				tmp *= prime[i];
				++ cnt;
			}
			ans += cnt - 1;
		}
		if (n > 1) ans += 1;
		cout << "Case #" << testcase << ": " << ans << endl;
	}
	return 0;
}

