#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
#include <stack>
using namespace std;

typedef pair<int, int> PII;

int val(char t) {
	if (t == 'C') return 0;
	else if (t == 'D') return 1;
	else if (t == 'H') return 2;
	else if (t == 'S') return 3;
	else return -1;
}

int p, m, n, top, cur, dir;
char buf[3];
PII deck[500], discard;
vector <PII> player[12];

void move() {
	cur += dir;
	if (cur == p) cur = 0;
	else if (cur < 0) cur = p - 1;
}

void draw(int p, int c) {
	for (int i = 0; i < c; ++ i) {
		if (top == n) break;
		player[p].push_back(deck[top ++]);
	}
}

void apply(PII discard) {
//	if (discard.first == 12) dir *= -1;
	if (discard.first == 7) {
		draw(cur, 2);
		move();
	} else if (discard.first == 1) {
		draw(cur, 1);
		move();
	} else if (discard.first == 11) {
		move();
	}
}

int drop() {
	int ret = -1;
	for (int i = 0; i < (int)player[cur].size(); ++ i)
		if (player[cur][i].first == discard.first || player[cur][i].second == discard.second) {
			if (ret == -1 || player[cur][i] > player[cur][ret])
				ret = i;
		}
	return ret;
}

void output(PII card) {
	printf("(%d,%d)", card.first, card.second);
}

int main() {
	while (1) {
		scanf("%d%d%d", &p, &m, &n);
		if (!p && !m && !n) break;
		for (int i = 0; i < n; ++ i) {
			scanf("%d%s", &deck[i].first, buf);
			deck[i].second = val(buf[0]);
		}
		top = 0;
		for (int i = 0; i < p; ++ i) {
			player[i].clear();
			for (int j = 0; j < m; ++ j)
				player[i].push_back(deck[top ++]);
		}
		discard = deck[top ++];
		cur = 0; dir = 1;
		if (discard.first == 12) dir *= -1;
		apply(discard);

		int times = 0;

		while (1) {
			/*cout << cur << ' ' << dir << endl;
			output(discard); puts("");
			for (int i = 0; i < p; ++ i) {
				for (int j = 0; j < (int)player[i].size(); ++ j)
					output(player[i][j]);
				puts("");
			}
			for (int i = top; i < n; ++ i)
				output(deck[i]);
			++ times;
			puts("");
			puts("");
			if (times > 10) break;*/

			int d = drop();
			if (d == -1) {
				draw(cur, 1);
				PII &card = player[cur].back();
				if (card.first == discard.first || card.second == discard.second) {
					player[cur].erase(player[cur].end() - 1);
					discard = card;
					if (discard.first == 12) dir *= -1;
					move();
					apply(discard);
				} else move();
			} else {
				discard = player[cur][d];
				player[cur].erase(player[cur].begin() + d);
				if (player[cur].size() == 0) {
					printf("%d\n", cur + 1);
					break;
				}
				if (discard.first == 12) dir *= -1;
				move();
				apply(discard);
			}
		}
	}
	return 0;
}
