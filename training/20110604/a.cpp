#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int n, row1, row2, col1, col2;

char gen(int i, int j) {
	int a = i / (2 * n - 1);
	int b = j / (2 * n - 1);
	int cx = (2 * n - 1) * a + n - 1;
	int cy = (2 * n - 1) * b + n - 1;
	int dx = abs(i - cx);
	int dy = abs(j - cy);
	if (dx + dy >= n) return '.';
	else return (char)('a' + ((dx + dy) % 26));
}

int main() {
	int ca = 0;
	while (scanf("%d%d%d%d%d", &n, &row1, &col1, &row2, &col2) == 5) {
		if (!n) break;
		printf("Case %d:\n", ++ ca);
		for (int i = row1; i <= row2; ++ i) {
			for (int j = col1; j <= col2; ++ j)
				putchar(gen(i, j));
			puts("");
		}
	}
	return 0;
}


