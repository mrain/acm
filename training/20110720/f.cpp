#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;
map <PII, int> hash;
int lch[300], rch[300], pnt[300];
int ra[300], rb[300];
string buf;
int n, hashcnt;
vector <int> app[300];

void build(int ind, int l, int r) {
	if (l == r) return;
	int stack = 0, sep = 0;
	for (int i = l + 1; i < r; ++ i) {
		if (buf[i] == '(') ++ stack;
		else if (buf[i] == ')') -- stack;
		if (!stack && buf[i] == ' ') {
			sep = i;
			break;
		}
	}
	lch[ind] = n; pnt[n ++] = ind;
	build(n - 1, l + 1, sep - 1);
	rch[ind] = n; pnt[n ++] = ind;
	build(n - 1, sep + 1, r - 1);
}

int dfs(int u) {
	if (lch[u] == -1) {
		app[u].clear();
		ra[u] = 0, rb[u] = 1;
		app[u].push_back(0);
		return 0;
	}
	int a = dfs(lch[u]), b = dfs(rch[u]), h;
	if (a > b) swap(a, b);
	PII t = make_pair(a, b);
	if (hash.find(t) == hash.end())
		hash[t] = h = hashcnt ++;
	else h = hash[t];

	app[u].clear();
	int la = app[lch[u]].size(), lb = app[rch[u]].size();
	for (int i = 0; i < la; ++ i) app[u].push_back(app[lch[u]][i]);
	for (int i = 0; i < lb; ++ i) app[u].push_back(app[rch[u]][i]);
	sort(app[u].begin(), app[u].end());
	app[u].erase(unique(app[u].begin(), app[u].end()), app[u].end());
	int l = app[u].size();
//	r[u] = ((double)la + lb - l) / (double)l;
	ra[u] = la + lb - l; rb[u] = l;
	app[u].push_back(h);
	return h;
}

int cmpf(int a1, int b1, int a2, int b2) {
	if (a1 * b2 == a2 * b1) return 0;
	else return a1 * b2 < a2 * b1 ? -1 : 1;
}

int cmp(int a, int b) {
	int t = cmpf(ra[a], rb[a], ra[b], rb[b]);
	if (t == 0) {
		int aa = lch[a], ab = rch[a], ba = lch[b], bb = rch[b];
		if (aa == -1) return 0;
//		if (rch[pnt[a]] == a) swap(aa, ab);
//		if (rch[pnt[b]] == b) swap(ba, bb);
		if (cmp(aa, ab) == -1) swap(aa, ab);
		if (cmp(ba, bb) == -1) swap(ba, bb);
		int k = cmp(aa, ba);
		if (k == 0) return cmp(ab, bb);
		else return k;
	} else return -t;
}

void maintain(int u, int type) {
	if (lch[u] == -1) return;
	int k = cmp(lch[u], rch[u]);
	if (type == 0 && k == -1) swap(lch[u], rch[u]);
	if (type == 1 && k == 1) swap(lch[u], rch[u]);
	maintain(lch[u], 0); maintain(rch[u], 1);
}

void print(int u) {
	if (lch[u] == -1) putchar('x');
	else {
		putchar('(');
		print(lch[u]);
		putchar(' ');
		print(rch[u]);
		putchar(')');
	}
}

int main() {
	while (getline(cin, buf) && buf[0] != '0') {
		hash.clear();
		memset(lch, 0xFF, sizeof(lch));
		memset(rch, 0xFF, sizeof(rch));
		memset(pnt, 0xFF, sizeof(pnt));
		n = 1; hashcnt = 1;
		build(0, 0, buf.size() - 1);
		dfs(0);
		maintain(0, 0);
//		for (int i = 0; i < n; ++ i)
//			printf("%d %.10f\n", i, r[i]);
		print(0);
		puts("");
	}
	return 0;
}

