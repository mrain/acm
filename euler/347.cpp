#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;

const int bound = 10000000;
bool notprime[bound], vis[bound];
int cnt, prime[bound / 10];
long long sum[bound / 10];

int calc(int p, int q) {
	int ret = 0;
	long long d = p * q;
	for (; d <= bound; d *= p) {
		int tmp = d;
		while (1LL * tmp * q <= bound) tmp *= q;
		ret = max(ret, tmp);
	}
	return ret;
}

int main() {
	for (int i = 2; i < bound; ++ i) {
		if (!notprime[i]) prime[++ cnt] = i;
		for (int j = 1; j <= cnt; ++ j) {
			if (1LL * i * prime[j] >= bound) break;
			notprime[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	for (int i = 1; i <= cnt; ++ i) sum[i] = sum[i - 1] + prime[i];
	long long ans = 0;
	for (int i = 1; 1LL * prime[i] * prime[i] <= bound; ++ i) {
		for (int j = i + 1; j <= cnt; ++ j) {
			int d = prime[i] * prime[j];
			if (bound / d == 0) break;
			if (bound / d >= 1) {
				ans += calc(prime[i], prime[j]);
			} else {
				int x = lower_bound(prime + 1, prime + cnt + 1, bound / prime[i] + 1) - prime - 1;
				ans += 1LL * prime[i] * (sum[x] - sum[j - 1]);
				break;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
