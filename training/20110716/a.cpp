#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int maxl[800010], maxr[800010], minl[800010], minr[800010];
int topmin[800010], sum[800010], topmax[800010], covermin[800010], covermax[800010];
bool rev[800010];
int a[800010];

void update(int ind) {
	maxl[ind] = max(maxl[ind << 1], sum[ind << 1] + maxl[(ind << 1) + 1]);
	minl[ind] = min(minl[ind << 1], sum[ind << 1] + minl[(ind << 1) + 1]);
	maxr[ind] = max(maxr[(ind << 1) + 1], sum[(ind << 1) + 1] + maxr[ind << 1]);
	minr[ind] = min(minr[(ind << 1) + 1], sum[(ind << 1) + 1] + minr[ind << 1]);
	covermax[ind] = min(min(minr[ind], minl[ind]), minr[ind << 1] + minl[(ind << 1) + 1]);
	covermin[ind] = max(max(maxr[ind], maxl[ind]), maxr[ind << 1] + maxl[(ind << 1) + 1]);
	topmax[ind] = max(covermax[ind], max(topmax[ind << 1], topmax[(ind << 1) + 1]));
	topmin[ind] = min(covermin[ind], min(topmin[ind << 1], topmin[(ind << 1) + 1]));
	sum[ind] = sum[ind << 1] + sum[(ind << 1) + 1];
}

void build(int l, int r, int ind) {
	if (l == r) {
		topmin[ind] = topmax[ind] = sum[ind] = maxl[ind] = maxr[ind] = minl[ind] = minr[ind] = a[l];
		covermin[ind] = covermax[ind] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, ind << 1);
	build(mid + 1, r, (ind << 1) + 1);
	update(ind);
}

void pp(int ind) {
	swap(maxl[ind], minl[ind]);
	maxl[ind] *= -1; minl[ind] *= -1;
	swap(maxr[ind], minr[ind]);
	maxr[ind] *= -1; minr[ind] *= -1;
	swap(topmin[ind], topmax[ind]);
	topmin[ind] *= -1; topmax[ind] *= -1;
	swap(covermax[ind], covermin[ind]);
	covermin[ind] *= -1, covermax[ind] *= -1;
	sum[ind] *= -1;
}

void expand(int l, int r, int ind) {
	if (!rev[ind]) return;
	if (l != r) {
		rev[ind << 1] ^= 1;
		pp(ind << 1);
		rev[(ind << 1) + 1] ^= 1;
		pp((ind << 1) + 1);
	}
	rev[ind] = false;
}

void reverse(int a, int b, int l, int r, int ind) {
	if (rev[ind]) expand(l, r, ind);
	if (a <= l && b >= r) {
		rev[ind] ^= 1;
		pp(ind);
		return;
	}
	int mid = (l + r) >> 1;
	if (a <= mid) reverse(a, b, l, mid, ind << 1);
	if (b > mid) reverse(a, b, mid + 1, r, (ind << 1) + 1);
	update(ind);
}

typedef pair<int, pair<int, int> > PIII;
const int inf = 2147483647;

PIII query(int a, int b, int l, int r, int ind) {
	if (rev[ind]) expand(l, r, ind);
	if (a <= l && b >= r) return make_pair(topmax[ind], make_pair(maxl[ind], maxr[ind]));
	int mid = (l + r) >> 1;
	PIII ret = make_pair(-inf, make_pair(-inf, -inf)), t1, t2;
	if (a <= mid)
		t1 = max(ret, query(a, b, l, mid, ind << 1));
	if (b > mid)
		t2 = max(ret, query(a, b, mid + 1, r, (ind << 1) + 1));
	if (a > r || b < l) return ret;
	if (a > mid) return t2;
	if (b <= mid) return t1;
	if (a <= mid && b > mid) {
		ret.first = max(t1.first, t2.first);
		ret.second.first = t1.second.first;
		ret.second.second = t2.second.second;
		ret.first = max(ret.first, t1.second.second + t2.second.first);
	}
	return ret;
}

int n, q, tests;

int main() {
	scanf("%d", &tests);
	while (tests --) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++ i)
			scanf("%d", a + i);
		build(0, n - 1, 0);
		scanf("%d", &q);
		for (int i = 0; i < q; ++ i) {
			int c, a, b;
			scanf("%d%d%d", &c, &a, &b);
			if (c == 0) reverse(a, b, 0, n - 1, 0);
			if (c == 1) printf("%d\n", query(a, b, 0, n - 1, 0).first);
		}
	}
	return 0;
}
