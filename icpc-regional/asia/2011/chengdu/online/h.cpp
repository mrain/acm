#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int mod = 1000000007;
int n, tests, neg, zero;
long long m;
int x[100010], ans;

int mul(int a, int b) {
	long long res = (long long)a * (long long)b;
	return res % mod;
}

void parseNegative() {
	if (!neg) return;
	int p = -x[neg - 1];
	if (m < p) p = m;
	x[neg - 1] += p; m -= p;
	if (x[neg - 1] == 0) ++ zero, -- neg;
}

void parseZero() {
	if (!zero) return;
	for (int i = neg + zero - 1; i >= neg; -- i)
		if (m > 0) ++ x[i], -- m, -- zero;
}

void parsePositive() {
	for (int i = neg + zero; i < n; ++ i)
		if (x[i] == 1 && m > 0) ++ x[i], -- m;

	int cnt = 0;
	for (int i = neg + zero; i < n; ++ i)
		if (x[i] == 2) ++ cnt;
	if (cnt == 1 && m == 2) return;

	for (int i = neg + zero; i < n; ++ i)
		if (x[i] == 2 && m > 0) ++ x[i], -- m;
}

int pow(int a, long long k) {
	int tmp = a, res = 1;
	while (k) {
		if (k & 1) res = mul(res, tmp);
		tmp = mul(tmp, tmp);
		k >>= 1ll;
	}
	return res;
}

int main() {
	scanf("%d", &tests);
	int cas = 0;
	while (tests --) {
		scanf("%d%lld", &n, &m);
		for (int i = 0; i < n; ++ i)
			scanf("%d", &x[i]);
		sort(x, x + n);
		neg = 0, zero = 0;
		for (int i = 0; i < n; ++ i) {
			if (x[i] < 0) ++ neg;
			else if (!x[i]) ++ zero;
		}
		if (neg & 1) parseNegative();
		if (zero) parseZero();
		parsePositive();
		
		ans = 1;
		if (m > 0) {
			if (m == 1) ++ x[neg + zero], -- m;

			if (m % 3 == 1 && m > 3)
				m -= 4, ans = 4;
			if (m / 3 > 0) ans = mul(ans, pow(3, m / 3));
			if (m % 3 > 0) ans = mul(ans, m % 3);
		}
		for (int i = 0; i < n; ++ i)
			ans = mul(ans, x[i]);
		printf("Case %d: %d\n", ++ cas, ans);
	}
	return 0;
}

