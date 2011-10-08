#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
using namespace std;
#define maxn 100010

map <int, int> pos;
int n, m, a[maxn], b[maxn];
char buf[200];
int cnt[maxn * 8], top[maxn * 8];

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

void build(int l, int r, int x) {
	cnt[x] = 0; top[x] = 1;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(l, mid, x + x);
	build(mid + 1, r, x + x + 1);
}

void update(int l, int r, int a, int d, int x) {
	if (l == a && r == a) {
		cnt[x] += d;
		if (cnt[x] == 0) top[x] = 1;
		else top[x] = b[a];
		return;
	}
	int mid = (l + r) >> 1;
	if (a <= mid) update(l, mid, a, d, x + x);
	else update(mid + 1, r, a, d, x + x + 1);

	if (cnt[x + x] == 0) top[x] = top[x + x + 1];
	else if (cnt[x + x + 1] == 0) top[x] = top[x + x];
	else top[x] = gcd(top[x + x], top[x + x + 1]);
	cnt[x] = cnt[x + x] + cnt[x + x + 1];
}

int main() {
	scanf("%d", &n); m = 0;
	for (int i = 0; i < n; ++ i) {
		scanf("%s%d", buf, a + i);
		if (pos.find(a[i]) == pos.end()) pos[a[i]] = ++ m, b[m] = a[i];
		a[i] *= (buf[0] == '+') ? 1 : -1;
	}
	build(1, m, 1);
	for (int i = 0; i < n; ++ i) {
		int p = a[i] > 0 ? a[i] : -a[i];
		int d = a[i] > 0 ? 1 : -1;
		update(1, m, pos[p], d, 1);
		printf("%d\n", top[1]);
	}
	return 0;
}

