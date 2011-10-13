#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int m = 21;
long long f[100000], sum[100000];

void init() {
	f[0] = 1; f[1] = 1; f[2] = 3; f[3] = 12;
	sum[0] = 0; sum[1] = 1; sum[2] = 4; sum[3] = 16;
	for (int i = 4; ; ++ i) {
		for (int a = 0; a < i; ++ a)
			for (int b = 0; a + b < i; ++ b)
				f[i] += f[a] * f[b] * f[i - a - b - 1];
		sum[i] = sum[i - 1] + f[i];
		if (sum[i] > 1000000000000001ll) break;
	}
}

int tests;
long long n;

long long calcdub(int cnt) {
	long long ret = 0;
	for (int i = 0; i <= cnt; ++ i)
		ret += f[i] * f[cnt - i];
	return ret;
}

void print(long long id, int cnt) {
	-- cnt;
	long long tmp = 0;
	if (cnt) {
		int cntl = 0;
		while (id >= f[cntl] * calcdub(cnt - cntl)) id -= f[cntl] * calcdub(cnt - cntl), ++ cntl;
		tmp = calcdub(cnt - cntl);
		if (cntl) {
			putchar('(');
			print(id / tmp, cntl);
			putchar(')');
		}
		id %= tmp; cnt -= cntl;

		int cntm = 0;
		while (id >= f[cntm] * f[cnt - cntm]) id -= f[cntm] * f[cnt - cntm], ++ cntm;
		if (cntm) {
			putchar('(');
			print(id / f[cnt - cntm], cntm);
			putchar(')');
		}
		id %= f[cnt - cntm]; cnt -= cntm;

		if (cnt) {
			putchar('(');
			print(id, cnt);
			putchar(')');
		}
	}
	putchar('X');
}

int main() {
	init();
	cin >> tests; int ca = 0;
	while (tests --) {
		cin >> n;
		printf("Case #%d: ", ++ ca);
		int cnt = lower_bound(sum, sum + 21, n) - sum;
		print(n - sum[cnt - 1] - 1, cnt);
		puts("");
	}
	return 0;
}
