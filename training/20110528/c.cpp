#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int d[1010][1010], r[1010][1010], n;

void movenext(int &x, int &y, int i) {
	if (x == i && y != n - i - 1) ++ y;
	else if (y == n - i - 1 && x != n - i - 1) ++ x;
	else if (x == n - i - 1 && y != i) -- y;
	else if (y == i && x != i) -- x;
}

bool check() {
	int l = (n >> 1) + (n & 1);
	for (int i = 0; i < l; ++ i) {
		int x = i, y = i;
		while (d[x][y] != r[i][i]) {
			movenext(x, y, i);
			if (x == i && y == i) return false;
		}
		int a = i, b = i;
		do {
			movenext(x, y, i);
			movenext(a, b, i);
			if (d[x][y] != r[a][b]) return false;
		} while (a != i || b != i);
	}
	return true;
}

int main() {
	int ca = 0;
	while (1) {
		scanf("%d", &n);
		if (!n) break;
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < n; ++ j)
				scanf("%d", &d[i][j]), r[i][j] = (i * n) + j + 1;
		printf("%d. %s\n", ++ ca, check() ? "YES" : "NO");
	}
	return 0;
}

