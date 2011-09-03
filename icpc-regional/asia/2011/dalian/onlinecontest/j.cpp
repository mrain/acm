#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define MaxN 300010

int Lch[MaxN], Rch[MaxN], Pnt[MaxN], Data[MaxN], Top[MaxN];
int Cov[MaxN], Rev[MaxN], List[MaxN], Total;

inline bool isRoot(int t) {
	return (!Pnt[t] || (Lch[Pnt[t]] != t && Rch[Pnt[t]] != t));
}

inline void Reverse(int cur) {
	if (!Rev[cur]) return;
	swap(Lch[cur], Rch[cur]);
	Rev[Lch[cur]] ^= 1; Rev[Rch[cur]] ^= 1;
	Rev[cur] = Rev[0] = 0;
}

inline void Update(int cur) {
	if (!cur) return;
	Top[cur] = max(Data[cur], max(Top[Lch[cur]], Top[Rch[cur]]) + Cov[cur]);
}

inline void Expand(int cur) {
	if (!cur || !Cov[cur]) return;
	Cov[Lch[cur]] += Cov[cur]; Data[Lch[cur]] += Cov[cur];
	Cov[Rch[cur]] += Cov[cur]; Data[Rch[cur]] += Cov[cur];
	Update(Lch[cur]); Update(Rch[cur]);
	Cov[cur] = Cov[0] = Top[0] = Data[0] = 0;
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
	Update(pnt); Update(cur);
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
	Update(pnt); Update(cur);
}

void Splay(int cur) {
	int pnt, anc;
	List[++ Total] = cur;
	for (int i = cur; !isRoot(i); i = Pnt[i]) List[++ Total] = Pnt[i];
	for (; Total; -- Total) {
		if (Rev[List[Total]]) Reverse(List[Total]);
		if (Cov[List[Total]]) Expand(List[Total]);
	}
	while (!isRoot(cur)) {
		pnt = Pnt[cur]; anc = Pnt[pnt];
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
	for (; u; u = Pnt[u]) Splay(u), Rch[u] = v, v = u, Update(u);
	for (; Lch[v]; v = Lch[v]);
	return v;
}

void Query(int x, int y) {
	int rx = Expose(x), ry = Expose(y);
	if (rx != ry) puts("-1");
	else {
		for (int u = x, v = 0; u; u = Pnt[u]) {
			Splay(u);
			if (!Pnt[u]) {
				printf("%d\n", max(Top[Rch[u]], max(Data[u], Top[v])));
				return;
			}
			Rch[u] = v; Update(u); v = u;
		}
	}
}

void Modify(int x, int y, int w) {
	int rx = Expose(x);
	int ry = Expose(y);
	if (rx != ry) puts("-1");
	else {
		for (int u = x, v = 0; u; u = Pnt[u]) {
			Splay(u);
			if (!Pnt[u]) {
				Cov[Rch[u]] += w; if (v != Rch[u]) Cov[v] += w;
				Data[Rch[u]] += w; if (v != Rch[u]) Data[v] += w;
				Update(Rch[u]); if (v != Rch[u]) Update(v);
				Data[0] = Cov[0] = Top[0] = 0;
				Data[u] += w; Update(u);
				return;
			}
			Rch[u] = v; Update(u); v = u;
		}
	}
}

void Join(int x, int y) {
	int rx = Expose(x), ry = Expose(y);
	if (rx == ry) puts("-1");
	else {
		Splay(x);
		Rch[x] = 0; Rev[x] = 1; Pnt[x] = y; Update(x);
	}
}

void Cut(int x, int y) {
	int rx = Expose(x), ry = Expose(y);
	if (rx != ry || x == y) puts("-1");
	else {
		Expose(x); Splay(x);
		Rch[x] = 0; Rev[x] = 1; Pnt[x] = 0; Update(x);

		Expose(y); Splay(y);
		int k = Lch[y]; Splay(k);
		if (Lch[y]) Pnt[Lch[y]] = Pnt[y], Rch[Pnt[y]] = Lch[y];
		else Rch[Pnt[y]] = 0;
		int tmp = Pnt[y];
		Lch[y] = Pnt[y] = 0;
		while (tmp) Update(tmp), tmp = Pnt[tmp];
		Update(y);
	}
}

int n, x, y, op, q, w;
int a[MaxN], b[MaxN];

int main() {
	while (scanf("%d", &n) == 1) {
		memset(Cov, 0, sizeof(Cov));
		memset(Data, 0, sizeof(Data));
		memset(Rev, 0, sizeof(Rev));
		memset(Top, 0, sizeof(Top));
		memset(Lch, 0, sizeof(Lch));
		memset(Rch, 0, sizeof(Rch));
		memset(Pnt, 0, sizeof(Pnt));
		for (int i = 1; i < n; ++ i) scanf("%d%d", a + i, b + i);
		for (int i = 1; i <= n; ++ i) {
			scanf("%d", Data + i);
			Top[i] = Data[i];
		}
		for (int i = 1; i < n; ++ i)
			Join(a[i], b[i]);
		scanf("%d", &q);
		for (int t = 0; t < q; ++ t) {
			scanf("%d%d%d", &op, &x, &y);
			if (op == 1) Join(x, y);
			else if (op == 2) Cut(x, y);
			else if (op == 3) {
				scanf("%d", &w);
				Modify(y, w, x);
/*				puts("------------");
				for (int i = 1; i <= 5; ++ i)
					Query(i, i);
				puts("------------");*/
			} else if (op == 4) Query(x, y);
		}
		puts("");
	}
	return 0;
}

