#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

const int inf = 0x2FFFFFF;
int n, a[2010], b[2010];
int ll[2010 * 8], rr[2010 * 8], top[2010 * 8], sum[2010 * 8];

struct record{
	int l, r, res, sum;
	record(int l = inf, int r = inf, int res = inf, int sum = 0)
		: l(l), r(r), res(res), sum(sum) {}
};

void build(int l, int r, int x) {
	if (l == r) {
		ll[x] = rr[x] = top[x] = sum[x] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, x + x);
	build(mid + 1, r, x + x + 1);
	ll[x] = min(ll[x + x], sum[x + x] + ll[x + x + 1]);
	rr[x] = min(rr[x + x + 1], sum[x + x + 1] + rr[x + x]);
	sum[x] = sum[x + x] + sum[x + x + 1];
	top[x] = min(min(top[x + x], top[x + x + 1]), ll[x + x + 1] + rr[x + x]);
}

record ask(int l, int r, int a, int b, int x) {
	if (a <= l && b >= r) return record(ll[x], rr[x], top[x], sum[x]);
	int mid = (l + r) >> 1;
	record r1, r2, ret;
	if (a <= mid) r1 = ask(l, mid, a, b, x + x);
	if (b > mid) r2 = ask(mid + 1, r, a, b, x + x + 1);
	ret.l = min(r1.l, r1.sum + r2.l);
	ret.r = min(r2.r, r2.sum + r1.r);
	ret.res = min(min(r1.res, r2.res), r1.r + r2.l);
	ret.sum = r1.sum + r2.sum;
	return ret;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d", a + i);
	for (int i = 0; i < n; ++ i) scanf("%d", b + i), b[i] += a[i];
	build(0, n - 1, 1);
	int ans = -inf;
	for (int i = 0; i < n; ++ i) {
		int cnt = b[i];
		for (int j = i + 1; j < n; ++ j) {
			cnt += b[j];
			if (j - i < 2) continue;
			int t = ask(0, n - 1, i + 1, j - 1, 1).res;
//			cout << i + 1 << ' ' << j - 1 << ' ' << t << endl;
			if (cnt - t > ans) ans = cnt - t;
		}
	}
	cout << ans << endl;
	return 0;
}

