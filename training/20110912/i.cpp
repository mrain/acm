#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
#define MaxN 200010

typedef pair<int, int> PII;
int Lch[MaxN], Rch[MaxN], Pnt[MaxN], Rev[MaxN], Sum[MaxN];
int List[MaxN], Total, n, b[MaxN];
PII a[MaxN];

inline void Reverse(int cur) {
	if (!Rev[cur]) return;
	swap(Lch[cur], Rch[cur]);
	Rev[Lch[cur]] ^= 1; Rev[Rch[cur]] ^= 1;
	Rev[cur] = Rev[0] = 0;
}

inline void Update(int cur) {
	if (!cur) return;
	Sum[cur] = Sum[Lch[cur]] + Sum[Rch[cur]] + 1;
}

void LeftRotate(int cur) {
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

void Splay(int cur, int root) {
	int pnt, anc; Total = 0;
	List[++ Total] = cur;
	for (int i = cur; Pnt[i]; i = Pnt[i]) List[++ Total] = Pnt[i];
	for (; Total; -- Total)
		if (Rev[List[Total]]) Reverse(List[Total]);
	while (Pnt[cur] != root) {
		pnt = Pnt[cur], anc = Pnt[pnt];
		if (Pnt[pnt] == root) {
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

void dfs(int i) {
	if (!i) return;
	if (Rev[i]) Reverse(i);
	dfs(Lch[i]);
	printf("%d ", i);
	dfs(Rch[i]);
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		memset(Lch, 0, sizeof(Lch));
		memset(Rch, 0, sizeof(Rch));
		memset(Pnt, 0, sizeof(Pnt));
		memset(Rev, 0, sizeof(Rev));
		memset(Sum, 0, sizeof(Sum));
		for (int i = 1; i <= n; ++ i) {
			scanf("%d", &Total);
			a[i] = make_pair(Total, i);
		}
		sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; ++ i) b[a[i].second] = i;
		Sum[b[1]] = 1;
		for (int i = 2; i <= n; ++ i) {
			Sum[b[i]] = i;
			Lch[b[i]] = b[i - 1];
			Pnt[b[i - 1]] = b[i];
		}
		Sum[n + 1] = n + 1; Lch[n + 1] = b[n]; Pnt[b[n]] = n + 1;

		if (n > 1) {
			Splay(1, 0);
			printf("%d ", Sum[Lch[1]] + 1);
			int tmp = Rch[1];
			if (Rev[tmp]) Reverse(tmp);
			while (Lch[tmp]) {
				tmp = Lch[tmp];
				if (Rev[tmp]) Reverse(tmp);
			}
			Splay(tmp, 0);
			Rev[Lch[tmp]] ^= 1;
//			dfs(tmp); puts("");
		}

		for (int i = 2; i < n; ++ i) {
			Splay(i, 0);
			printf("%d ", Sum[Lch[i]] + 1);
			int tmp = Rch[i];
			if (Rev[tmp]) Reverse(tmp);
			while (Lch[tmp]) {
				tmp = Lch[tmp];
				if (Rev[tmp]) Reverse(tmp);
			}
			Splay(i - 1, 0);
			Splay(tmp, i - 1);
			Rev[Lch[tmp]] ^= 1;
//			dfs(i - 1); puts("");
		}
		printf("%d\n", n);
	}
	return 0;
}
