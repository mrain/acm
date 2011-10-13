#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;

const int mask = (1 << 15) - 1;
int bitcnt[1<<15], tests, n, l2[1<<15];
long long a[16], f[1<<15], A[1<<15], sum[1<<15];

long long calc(long long a) {
	return 1ll << ((long long)(bitcnt[a & mask] + bitcnt[(a >> 15ll) & mask] + bitcnt[(a >> 30) & mask]));
}

int main() {
	for (int i = 1; i < 1<<15; ++ i)
		bitcnt[i] = bitcnt[i - (i & (-i))] + 1;
	for (int i = 0; i < 15; ++ i)
		l2[1 << i] = i;
	cin >> tests;
	for (int ca = 1; ca <= tests; ++ ca) {
		cin >> n;
		for (int i = 0; i < n; ++ i) cin >> a[i];
		long long ans = 0;
		for (int i = (1<<n) - 1; i; -- i) {
			int k = ((1 << n) - 1) ^ i;
			A[i] = (1ll << 45ll) - 1ll;
			for (int j = 0; j < n; ++ j)
				if (i & (1<<j)) A[i] &= a[j];
			f[i] = calc(A[i]);
			for (int j = k; j; j = (j - 1) & k)
				f[i] -= f[i + j];
			if (bitcnt[i] & 1) ans += f[i];
		}
		cout << "Case #" << ca << ": " << ans << endl;
	}
	return 0;
}

