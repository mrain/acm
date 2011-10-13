#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

struct segment {
	short x1, y1, x2, y2;
	char d;
	segment() {}
	segment(int x1, int y1, int x2, int y2, int d = 0)
		: x1(x1), y1(y1), x2(x2), y2(y2), d(d) {}
};

int tests, k, X1, Y1, X2, Y2;
queue <segment> f[2];

inline void push(queue<segment> &q, const segment &l) {
	if (l.d == 4 && l.x1 < X1) return;
	if (l.d == 2 && l.x1 > X2) return;
	if (l.d == 1 && l.y1 > Y2) return;
	if (l.d == 3 && l.y1 < Y1) return;
	q.push(l);
}

void extend(queue <segment> &q, const segment &l) {
	if (l.d & 1) {
		int y = l.y1, x1 = l.x1, x2 = l.x2;
		if (x1 > x2) swap(x1, x2);
		int len = (x2 - x1) / 3;
		int ny = y + len * (l.d == 3 ? -1 : 1);
		push(q, segment(x1, y, x1 + len, y, l.d));
		push(q, segment(x2 - len, y, x2, y, l.d));
		push(q, segment(x1 + len, ny, x2 - len, ny, l.d));
		push(q, segment(x1 + len, min(y, ny), x1 + len, max(y, ny), 4));
		push(q, segment(x2 - len, min(y, ny), x2 - len, max(y, ny), 2));
	} else {
		int x = l.x1, y1 = l.y1, y2 = l.y2;
		if (y1 > y2) swap(y1, y2);
		int len = (y2 - y1) / 3;
		int nx = x + len * (l.d == 4 ? -1 : 1);
		push(q, segment(x, y1, x, y1 + len, l.d));
		push(q, segment(x, y2 - len, x, y2, l.d));
		push(q, segment(nx, y1 + len, nx, y2 - len, l.d));
		push(q, segment(min(x, nx), y1 + len, max(x, nx), y1 + len, 3));
		push(q, segment(min(x, nx), y2 - len, max(x, nx), y2 - len, 1));
	}
}

char ans[200][200];

void update(char &c, char s) {
	if (c == s) return;
	if (c == '.') c = s;
	else c = '+';
}

void print(queue <segment> &q) {
	for (int i = 0; i < X2 - X1; ++ i)
		for (int j = 0; j < Y2 - Y1; ++ j)
			ans[i][j] = '.';
	while (!q.empty()) {
		segment s = q.front(); q.pop();
		if ((s.d & 1) == 0) {
			int x = s.x1, y1 = s.y1, y2 = s.y2;
			if (y1 > y2) swap(y1, y2);
			x -= X1, y1 -= Y1, y2 -= Y1;
			y1 = max(0, y1); y2 = min(Y2 - Y1, y2);
			if (x >= 0 && x < X2 - X1)
				for (int j = y1; j <= y2; ++ j)
					update(ans[j][x], '|');
		} else {
			int y = s.y1, x1 = s.x1, x2 = s.x2;
			if (x1 > x2) swap(x1, x2);
			y -= Y1, x1 -= X1, x2 -= X1;
			x1 = max(0, x1); x2 = min(X2 - X1, x2);
			if (y >= 0 && y < Y2 - Y1)
				for (int j = x1; j <= x2; ++ j)
					update(ans[y][j], '-');
		}
	}
	for (int i = 0; i < X2 - X1; ++ i) {
		for (int j = 0; j < Y2 - Y1; ++ j)
			putchar(ans[i][j]);
		puts("");
	}
}

int main() {
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		scanf("%d %d %d", &k, &X1, &Y1);
//		k = 5;
		int tt = 3;
		for (int i = 1; i < k; ++ i) tt = tt * 3 + 2;
		tt = (tt - 1) / 2;
//		cout << tt << endl;
		X1 -= tt; Y1 -= tt;
		swap(X1, Y1);
//		X1 -= 1; Y1 -= 1;
		X2 = X1 + 10; Y2 = Y1 + 10;

		int tmp = 1;
		for (int i = 1; i < k; ++ i) tmp *= 3;
//		X1 = -tt, Y1 = -tt, X2 = tt + 1, Y2 = tt + 1;

		while (!f[0].empty()) f[0].pop();
		push(f[0], segment(-tmp, tmp, tmp, tmp, 1));
		push(f[0], segment(-tmp, -tmp, tmp, -tmp, 3));
		push(f[0], segment(tmp, -tmp, tmp, tmp, 2));
		push(f[0], segment(-tmp, -tmp, -tmp, tmp, 4));

		int now = 0, to = 1;
		for (int i = 1; i < k; ++ i) {
//			printf("%d\n", i);
//			print(f[now]);
			while (!f[to].empty()) f[to].pop();
			while (!f[now].empty()) {
				segment s = f[now].front(); f[now].pop();
				extend(f[to], s);
			}
			now ^= 1; to ^= 1;
		}
		printf("Case %d:\n", ++ ca);
		print(f[now]);
	}
	return 0;
}

