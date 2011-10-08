#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define MaxN 50010

int Lch[MaxN], Rch[MaxN], Pnt[MaxN];

inline int isRoot(int t) {
	return (!Pnt[t] || (Lch[Pnt[t]] != t && Rch[Pnt[t]] != t));
}

void LeftRotate(int cur) {
	if (isRoot(cur)) return;
	int pnt = Pnt[cur], anc = Pnt[pnt];
	Lch[pnt] = Rch[cur];
	if (Rch[cur]) Pnt[Rch[cur]] = pnt;
	Rch[cur] = pnt; Pnt[pnt] = cur;
	Pnt[cur] = anc;
	if (anc) {
		if (Lch[anc] == pnt) Lch[anc] = cur;
		else if (Rch[anc] == pnt) Rch[anc] = cur;
	}
}

void RightRotate(int cur) {
	if (isRoot(cur)) return;
	int pnt = Pnt[cur], anc = Pnt[pnt];
	Rch[pnt] = Lch[cur];
	if (Lch[cur]) Pnt[Lch[cur]] = pnt;
	Lch[cur] = pnt; Pnt[pnt] = cur;
	Pnt[cur] = anc;
	if (anc) {
		if (Lch[anc] == pnt) Lch[anc] = cur;
		else if (Rch[anc] == pnt) Rch[anc] = cur;
	}
}

void Splay(int cur) {
	int pnt, anc;
	while (!isRoot(cur)) {
		pnt = Pnt[cur], anc = Pnt[pnt];
		if (isRoot(pnt)) {
			if (Lch[pnt] == cur) LeftRotate(cur);
			else RightRotate(cur);
		} else {
			if (Lch[anc] == pnt) {
				if (Lch[pnt] == cur) LeftRotate(pnt);
				else RightRotate(cur);
				LeftRotate(cur);
			} else {
				if (Lch[pnt] == cur) LeftRotate(cur);
				else RightRotate(pnt);
				RightRotate(cur);
			}
		}
	}
}

int Expose(int u) {
	int v = 0;
	for (; u; u = Pnt[u]) Splay(u), Rch[u] = v, v = u;
	for (; Lch[v]; v = Lch[v]);
	return v;
}

void Move(int x, int y) {
	if (y) {
		Expose(x); Splay(x);
		int v = 0, p = y, u = y;
		for (; u; u = Pnt[u]) {
			Splay(u); Rch[u] = v; v = u;
			if (Pnt[u]) p = Pnt[u];
		}
		if (p == x) return;
	}
	Expose(x); Splay(x);
	if (Lch[x]) {
		Pnt[Lch[x]] = Pnt[x];
		Lch[x] = 0;
	}
	Pnt[x] = y;
}

int tests, n, m;
char buf[300];

int main() {
	bool first = true;
	while (1) {
		if (scanf("%d", &n) != 1) break;
		if (!first) puts(""); first = false;
		memset(Lch, 0, sizeof(Lch));
		memset(Rch, 0, sizeof(Rch));
		memset(Pnt, 0, sizeof(Pnt));
//		scanf("%d", &n);
		for (int i = 1; i <= n; ++ i) scanf("%d", &Pnt[i]);
		scanf("%d", &m);
		for (int i = 1; i <= m; ++ i) {
			int x, y;
			scanf("%s%d", buf, &x);
			if (buf[0] == 'Q') printf("%d\n", Expose(x));
			else {
				scanf("%d", &y);
				Move(x, y);
			}
		}
	}
	return 0;
}
