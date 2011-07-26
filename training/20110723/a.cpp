#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

char a[2001][2001];
int f[2001][2001][5];
int blank, n, m;
bool xfinish, ofinish;
int xcnt, ocnt;

inline int abs(int a) { return a < 0 ? -a : a; }

bool analysiso() {
	bool ofinish = 0;
	memset(f, 0, sizeof(f));
	for (int i = 0; i < n && !ofinish; ++ i)
		for (int j = 0; j < n; ++ j)
			if (a[i][j] == 'O') {
				f[i][j][0] = f[i][j][1] = f[i][j][2] = f[i][j][3] = 1;
				if (j) f[i][j][0] = f[i][j - 1][0] + 1;
				if (i) f[i][j][1] = f[i - 1][j][1] + 1;
				if (i && j) f[i][j][2] = f[i - 1][j - 1][2] + 1;
				if (i && j < n - 1) f[i][j][3] = f[i - 1][j + 1][3] + 1;
				if (f[i][j][0] >= m || f[i][j][1] >= m || f[i][j][2] >= m || f[i][j][3] >= m) {
					ofinish = true;
					break;
				}
			}
	return ofinish;
}

bool analysisx() {
	bool xfinish = 0;
	memset(f, 0, sizeof(f));
	for (int i = 0; i < n && !xfinish; ++ i)
		for (int j = 0; j < n; ++ j)
			if (a[i][j] == 'X') {
				f[i][j][0] = f[i][j][1] = f[i][j][2] = f[i][j][3] = 1;
				if (j) f[i][j][0] = f[i][j - 1][0] + 1;
				if (i) f[i][j][1] = f[i - 1][j][1] + 1;
				if (i && j) f[i][j][2] = f[i - 1][j - 1][2] + 1;
				if (i && j < n - 1) f[i][j][3] = f[i - 1][j + 1][3] + 1;
				if (f[i][j][0] >= m || f[i][j][1] >= m || f[i][j][2] >= m || f[i][j][3] >= m) {
					xfinish = true;
					break;
				}
			}
	return xfinish;
}

void analysis() {
	blank = 0;
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j) {
			if (a[i][j] == '.') ++ blank;
			if (a[i][j] == 'X') ++ xcnt;
			if (a[i][j] == 'O') ++ ocnt;
		}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i)
		scanf("%s", a[i]);
	analysis();
	xfinish = analysisx();
	ofinish = analysiso();
	if (xfinish && ofinish) {
		puts("ERROR");
		return 0;
	}
	if (xcnt - ocnt > 1 || ocnt > xcnt) {
		puts("ERROR");
		return 0;
	}
	if ((xfinish && ocnt == xcnt) || (ofinish && xcnt != ocnt)) {
		puts("ERROR");
		return 0;
	}
	if (xfinish) {
		bool flag = false;
		for (int i = 0; i < n && !flag; ++ i)
			for (int j = 0; j < n; ++ j) {
				if (a[i][j] != 'X') continue;
				a[i][j] = '.';
				if (!analysisx()) {
					flag = true;
					break;
				}
				a[i][j] = 'X';
			}
		if (!flag) {
			puts("ERROR");
			exit(0);
		}
	}
	if (ofinish) {
		bool flag = false;
		for (int i = 0; i < n && !flag; ++ i)
			for (int j = 0; j < n; ++ j) {
				if (a[i][j] != 'O') continue;
				a[i][j] = '.';
				if (!analysiso()) {
					flag = true;
					break;
				}
				a[i][j] = 'O';
			}
		if (!flag) {
			puts("ERROR");
			exit(0);
		}
	}
	if (xfinish) puts("X WINS");
	else if (ofinish) puts("O WINS");
	else if (blank) puts("IN PROGRESS");
	else puts("DRAW");
	return 0;
}

