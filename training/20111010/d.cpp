#include <cstdio>
#include <cstdlib>
#include <set>
#include <cstring>
#include <iostream>
using namespace std;

const int m = 8;

struct permutation{
	int p[8];
	permutation() {
		for (int i = 0; i < m; ++ i) p[i] = i;
	}
	int operator [](int i) const { return p[i]; }
	int length() const {
		static bool vis[8];
		int ret = 0;
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < m; ++ i) {
			if (vis[i]) continue;
			++ ret;
			int x = i;
			while (!vis[x]) {
				vis[x] = true;
				x = p[x];
			}
		}
		return ret;
	}
	void print() const {
		putchar('(');
		for (int i = 0; i < m - 1; ++ i)
			printf("%d,", p[i]);
		printf("%d)", p[m - 1]);
	}
};
permutation operator *(const permutation &a, const permutation &b) {
	permutation ret;
	for (int i = 0; i < m; ++ i)
		ret.p[i] = a[b[i]];
	return ret;
}
bool operator <(const permutation &a, const permutation &b) {
	for (int i = 0; i < m; ++ i)
		if (a.p[i] != b.p[i]) return a.p[i] < b.p[i];
	return false;
}
bool operator ==(const permutation &a, const permutation &b) {
	for (int i = 0; i < m; ++ i)
		if (a[i] != b[i]) return false;
	return true;
}

permutation x, y, z, xx, yy, aa, bb, check;
set<permutation> s;
int stack[10000], top;

void setp(permutation &p, int a, int b, int c, int d) {
	-- a; -- b; -- c; -- d;
	p.p[a] = b; p.p[b] = c; p.p[c] = d; p.p[d] = a;
} 
void setp(permutation &p, int a, int b, int c) {
	-- a; -- b; -- c;
	p.p[a] = b; p.p[b] = c; p.p[c] = a;
} 

void dfs(permutation t) {
	s.insert(t);
	permutation a = t * x, b = t * y, c = t * z, d = t * xx, e = t * yy;
	permutation f = t * aa, g = t * bb;
	if (!s.count(a)) stack[++ top] = 1, dfs(a), -- top;
	if (!s.count(b)) stack[++ top] = 2, dfs(b), -- top;
	if (!s.count(c)) stack[++ top] = 3, dfs(c), -- top;
/*	if (!s.count(d)) stack[++ top] = 4, dfs(d), -- top;
	if (!s.count(e)) stack[++ top] = 5, dfs(e), -- top;
	if (!s.count(f)) stack[++ top] = 6, dfs(f), -- top;
	if (!s.count(g)) stack[++ top] = 7, dfs(g), -- top;*/
}

void init() {
	setp(x, 1, 2, 3, 4);
	setp(x, 5, 6, 7, 8);
	setp(y, 1, 2, 6, 5);
	setp(y, 4, 3, 7, 8);
	setp(z, 1, 4, 8, 5);
	setp(z, 2, 3, 7, 6);
	setp(xx, 1, 3, 6);
	setp(xx, 4, 7, 5);
	setp(yy, 4, 2, 5);
	setp(yy, 3, 8, 6);
	setp(aa, 2, 4, 7);
	setp(aa, 1, 8, 6);
	setp(bb, 1, 3, 8);
	setp(bb, 2, 7, 5);
	permutation t;
	check.p[0] = 1; check.p[1] = 0; check.p[4] = 5; check.p[5] = 4;
	dfs(t);
//	cout << s.count(t) << endl;
//	if (s.count(xx)) cout << "!" << endl;
//	x.print(); y.print();
//	(x*y).print();
//	x.print(); y.print(); z.print();
/*	permutation t, tx, ty;
	for (int a = 0; a <= 4; ++ a) {
		tx = t;
		for (int b = 0; b <= 4; ++ b) {
			ty = tx;
			for (int c = 0; c <= 4; ++ c) {
				s.insert(ty);
				ty = ty * z;
			}
			tx = tx * y;
		}
		t = t * x;
	}*/
}

int main() {
	init();
	cout << s.size() << endl;
	int cnt[10], ans;
	memset(cnt, 0, sizeof(cnt));
	for (set<permutation>::iterator it = s.begin(); it != s.end(); ++ it) {
//		it->print();
		ans += 1<<(it->length());
		++ cnt[it->length()];
//		printf(" %d\n", it->length());
	}
	cout << ans << endl;
	cout << 23 * 24 << endl;
	for (int i = 1; i <= 8; ++ i)
		printf("%d %d\n", i, cnt[i]);
	return 0;
}

