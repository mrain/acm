#include <cstdio>
#include <cctype>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int p[255];
int l[10][100], r[10][100];
int a[100];
bool vis[100];
char s[1000010];
int n;

long long gcd(long long a, long long b) {
	return b == 0 ? a : gcd(b, a % b);
}

void _(int id, int a, int b, int c, int d) {
	l[id][a] = b; r[id][a] = d;
	l[id][b] = c; r[id][b] = a;
	l[id][c] = d; r[id][c] = b;
	l[id][d] = a; r[id][d] = c;
}

void init() {
	for (int k = 1; k <= 8; ++ k)
		for (int i = 1; i <= 54; ++ i)
			l[k][i] = r[k][i] = i;
	p['u'] = p['U'] = 1;
	p['d'] = p['D'] = 2;
	p['l'] = p['L'] = 3;
	p['f'] = p['F'] = 4;
	p['b'] = p['B'] = 5;
	p['r'] = p['R'] = 6;

	_(1, 1, 3, 9, 7);
	_(1, 2, 6, 8, 4);
	_(1, 19, 10, 37, 28);
	_(1, 20, 11, 38, 29);
	_(1, 21, 12, 39, 30);

	_(2, 46, 48, 54, 52);
	_(2, 49, 47, 51, 53);
	_(2, 25, 34, 43, 16);
	_(2, 26, 35, 44, 17);
	_(2, 27, 36, 45, 18);

	_(3, 10, 12, 18, 16);
	_(3, 11, 15, 17, 13);
	_(3, 22, 49, 42, 4);
	_(3, 25, 52, 39, 7);
	_(3, 19, 46, 45, 1);

	_(4, 19, 21, 27, 25);
	_(4, 20, 24, 26, 22);
	_(4, 7, 28, 48, 18);
	_(4, 8, 31, 47, 15);
	_(4, 9, 34, 46, 12);

	_(5, 37, 39, 45, 43);
	_(5, 38, 42, 44, 40);
	_(5, 30, 1, 16, 54);
	_(5, 33, 2, 13, 53);
	_(5, 36, 3, 10, 52);

	_(6, 28, 30, 36, 34);
	_(6, 29, 33, 35, 31);
	_(6, 9, 37, 54, 27);
	_(6, 6, 40, 51, 24);
	_(6, 3, 43, 48, 21);


	for (int i = 1; i <= 54; ++ i)
		a[i] = i;
}

void apply(int *b) {
	static int c[100];
	memcpy(c, a, sizeof(c));
	for (int i = 1; i <= 54; ++ i)
		a[i] = c[b[i]];
}

int main() {
	init();
	gets(s);
	int len = strlen(s);
	for (int i = 0; i < len; ++ i) {
		int id = p[s[i]];
		if (isupper(s[i])) apply(l[id]);
		else apply(r[id]);
	}

	memset(vis, 0, sizeof(vis));
	long long ans = 1;
	for (int i = 1; i <= 54; ++ i)
		if (!vis[i]) {
			int cur = i, cnt = 0;
			while (!vis[cur]) {
				++ cnt;
				vis[cur] = true;
				cur = a[cur];
			}
			ans = ans / gcd(ans, cnt) * cnt;
		}
	cout << ans - 1 << endl;
	return 0;
}

