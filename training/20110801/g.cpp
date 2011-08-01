#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

typedef pair<int, int> PII;
typedef priority_queue<PII> heap;
int tests, n, m, p;
int q[200010], cov[200010 * 4];
int cover[200010 * 4], top[200010 * 4], tid[200010 * 4];
bool vis[200010];
heap h[2000];

int query(int x) {
	int l = 0, r = n - 1, i = 1, ret = 0;
	while (l != r) {
		ret += cover[i];
		int mid = (l + r) >> 1;
		if (x <= mid) r = mid, i += i; 
		else l = mid + 1, i += i + 1;
	}
	return ret + cover[i];
}

int query1(int x) {
	int l = 0, r = n - 1, i = 1, ret = 0;
	while (l != r) {
		ret += cov[i];
		int mid = (l + r) >> 1;
		if (x <= mid) r = mid, i += i; 
		else l = mid + 1, i += i + 1;
	}
	return ret + cov[i];
}

void set(int x) {
	int l = 0, r = n - 1, i = 1, cnt = 0;
	while (l != r) {
		cnt += cover[i];
		int mid = (l + r) >> 1;
		if (x <= mid) r = mid, i += i; 
		else l = mid + 1, i += i + 1;
	}
	cover[i] = -cnt;
}

void mask(int a, int b, int l, int r, int i, int v) {
	if (a <= l && b >= r) {
		cover[i] += v;
		return;
	}
	int mid = (l + r) >> 1;
	if (a <= mid) mask(a, b, l, mid, i + i, v);
	if (b > mid) mask(a, b, mid + 1, r, i + i + 1, v);
}

void mask1(int a, int b, int l, int r, int i, int v) {
	if (a <= l && b >= r) {
		cov[i] += v;
		if (tid[i] != -1) top[i] += v;
		return;
	}
	int mid = (l + r) >> 1;
	if (a <= mid) mask1(a, b, l, mid, i + i, v);
	if (b > mid) mask1(a, b, mid + 1, r, i + i + 1, v);
	mid = i + i;
	if (tid[mid + 1] != -1 && top[mid + 1] > top[mid]) ++ mid;
	if (tid[mid] == -1) top[i] = -2147483647, tid[i] = -1;
	else top[i] = top[mid] + cov[i], tid[i] = tid[mid];
}

void init(int l, int r, int i) {
	tid[i] = l;
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	init(l, mid, i + i), init(mid + 1, r, i + i + 1);
}

PII ask(int a, int b, int l, int r, int i) {
	if (a <= l && b >= r) return make_pair(top[i], tid[i]);
	if (tid[i] == -1) return make_pair(-2147483647, -1);
	int mid = (l + r) >> 1;
	PII ret(-2147483647, -1);
	if (a <= mid) ret = max(ret, ask(a, b, l, mid, i + i));
	if (b > mid) ret = max(ret, ask(a, b, mid + 1, r, i + i + 1));
	if (ret.second != -1) ret.first += cov[i];
	return ret;
}

void reset(int x, int l, int r, int i) {
	if (l == r) {
		tid[i] = -1;
		top[i] = -2147483647;
		return;
	}
	int mid = (l + r) >> 1;
	if (x <= mid) reset(x, l, mid, i + i);
	if (x > mid) reset(x, mid + 1, r, i + i + 1);
	mid = i + i;
	if (tid[mid + 1] != -1 && top[mid + 1] > top[mid]) ++ mid;
	if (tid[mid] == -1) top[i] = -2147483647, tid[i] = -1;
	else top[i] = top[mid] + cov[i], tid[i] = tid[mid];
}

int main() {
	scanf("%d", &tests);
	while (tests --) {
		memset(q, 0, sizeof(q));
		memset(cover, 0, sizeof(cover));
		memset(cov, 0, sizeof(cov));
		memset(top, 0, sizeof(top));
		memset(vis, 0, sizeof(vis));
		scanf("%d%d%d", &n, &m, &p);
		init(0, n - 1, 1);
		for (int i = 0; i < m; ++ i) {
//			cout << i << endl;
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			-- a, -- b;
			mask(a, b, 0, n - 1, 1, c);
			mask1(a, b, 0, n - 1, 1, c);
			while (1) {
				PII tmp = ask(a, b, 0, n - 1, 1);
				if (tmp.first >= p) {
					vis[tmp.second] = true;
					set(tmp.second);
					reset(tmp.second, 0, n - 1, 1);
				} else break;
			}
		}
		for (int i = 0; i < n; ++ i) {
			if (i) putchar(' ');
			int res = query1(i);
			if (vis[i]) res += query(i);
			printf("%d", res);
		}
		puts("");
	}
	return 0;
}

