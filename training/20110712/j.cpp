#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cctype>
using namespace std;

char A[300][300];
int x, y;
char command[300], text[30000];

inline int sgn(int a) {
	return a < 0 ? -1 : a > 0 ? 1 : 0;
}

inline int abs(int a) { return a < 0 ? -a : a; }

void fill(int a, int b, char c) {
	if (a <= 0 || b <= 0 || a > y || b > x) return;
	if (A[a][b] == c || A[a][b] == ' ' || c == ' ') {
		A[a][b] = c;
		return;
	}
	if ((A[a][b] == '/' && c == '\\') || (A[a][b] == '\\' && c == '/'))
		A[a][b] = 'x';
	else if ((A[a][b] == '-' && c == '|') || (A[a][b] == '|' && c == '-'))
		A[a][b] = '+';
	else if (A[a][b] == '+' && (c == '|' || c == '-'))
		return;
	else if (A[a][b] == 'x' && (c == '/' || c == '\\'))
		return;
	else A[a][b] = '*';
}

int main() {
	while (scanf("%d%d", &x, &y)) {
		if (x == 0 && y == 0) break;
		memset(A, ' ', sizeof(A));
		for (int i = 0; i <= y; ++ i) A[i][0] = A[i][x + 1] = '|';
		for (int i = 0; i <= x; ++ i) A[0][i] = A[y + 1][i] = '-';
		A[0][0] = A[y + 1][0] = A[0][x + 1] = A[y + 1][x + 1] = '+';
		while (1) {
			int a, b, c, d;
			scanf("%s", command);
			if (command[0] == 'C') {
				scanf("%d%d", &a, &b);
				scanf("%d%d", &c, &d);
				if (a > c) swap(a, c);
				if (b > d) swap(b, d);
				for (int i = a; i <= c; ++ i)
					for (int j = b; j <= d; ++ j)
						if (i > 0 && j > 0 && i <= x && j <= y)
							A[j][i] = ' ';
			} else if (command[0] == 'T') {
				scanf("%d%d", &a, &b);
				scanf("%s", text);
				int l = strlen(text);
				for (int i = 0; i < l && a + i <= x; ++ i)
					fill(b, a + i, text[i]);
			} else if (command[0] == 'P' && command[1] == 'O') {
				scanf("%d%d", &a, &b);
				fill(b, a, 'o');
			} else if (command[0] == 'L') {
				scanf("%d%d", &a, &b);
				scanf("%d%d", &c, &d);
				if (c != a && b != d && abs(c - a) != abs(b - d)) continue;
				if (a == c && b == d) continue;
				int dx = sgn(c - a), dy = sgn(d - b);
				char C;
				if (dx == 0) C = '|';
				else if (dy == 0) C = '-';
				else if (dx * dy == 1) C = '\\';
				else C = '/';
				for (int nx = a, ny = b; nx != c || ny != d; nx += dx, ny += dy)
					fill(ny, nx, C);
				fill(d, c, C);
			} else {
				for (int i = 0; i <= y + 1; ++ i) {
					for (int j = 0; j <= x + 1; ++ j)
						putchar(A[i][j]);
					puts("");
				}
				break;
			}
		}
		puts("");
	}
	return 0;
}

