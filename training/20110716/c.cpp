#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;

const int mod = 1000000007;
long long a[3][3], b[3][3], r[3][3];
int tests;
long long n;

void pow(long long n) {
	b[1][1] = b[0][0] = 1;
	b[1][0] = b[0][1] = 0;
	while (n) {
		if ((n & 1ll)) {
			memset(r, 0, sizeof(r));
			for (int i = 0; i < 2; ++ i)
				for (int j = 0; j < 2; ++ j)
					for (int k = 0; k < 2; ++ k) {
						r[i][j] += a[i][k] * b[k][j];
						r[i][j] %= mod;
					}
			memcpy(b, r, sizeof(r));
		}
		memset(r, 0, sizeof(r));
		for (int i = 0; i < 2; ++ i)
			for (int j = 0; j < 2; ++ j)
				for (int k = 0; k < 2; ++ k) {
					r[i][j] += a[i][k] * a[k][j];
					r[i][j] %= mod;
				}
		memcpy(a, r, sizeof(r));
		n >>= 1ll;
	}
}

int main() {
	cin >> tests;
	while (tests --) {
		cin >> n;
		a[0][0] = a[1][0] = a[0][1] = 1;
		a[1][1] = 0;
		pow(n + 1);
		if (n == 0) cout << 0 << endl;
		else if (n == 1) cout << 2 << endl;
		else cout << (b[0][1] + b[0][0]) % mod << endl;
	}
	return 0;
}
