#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int exgcd(int a, int b, int &x, int &y) {
	if (b == 0) {
		x = 1; y = 0;
		return a;
	} else {
		int t = exgcd(b, a % b, x, y);
		int tmp = x;
		x = y;
		y = tmp - (a / b) * y;
		return t;
	}
}

const int limit = 10000000;
int a, b;

int main() {
	int ca = 0;
	while (1) {
		scanf("%d%d", &a, &b);
		if (a == 0 && b == 0) break;
		if (a == 0 || b == 0) {
			if (a == 0) swap(a, b);
			printf("Case %d: %d\n", ++ ca, limit);
			continue;
		}
		int k = gcd(a, b);
		a /= k, b /= k;
		int x, y;
		exgcd(a, b, x, y);
		y *= -1;			//a*x - b*y = 1;
		while (x > 0 && y > 0) x -= b, y -= a;
		while (x < 0 || y < 0) x += b, y += a;
		int ans = min((limit - x) / b, (limit - y) / a) + 1;
		if (x > limit || y > limit) ans = 0;
		x *= -1, y *= -1;
		while (x > 0 && y > 0) x -= b, y -= a;
		while (x < 0 || y < 0) x += b, y += a;
		if (x <= limit && y <= limit)
			ans += min((limit - x) / b, (limit - y) / a) + 1;
		printf("Case %d: %d\n", ++ ca, ans);
	}
	return 0;
}

