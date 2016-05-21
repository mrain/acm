#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

const int threshold = 320;

int T, n, m, color[100010], ans;
vector <int> e[100010], l[100010];
map <int, int> cnt[100010];

void change_color(int x, int y) {
	if (color[x] == y) return;
	int now = color[x], cnow = 0, cafter = 0;
	if (e[x].size() >= threshold) {
		cnow = cnt[x].count(now) == 0 ? 0 : cnt[x][now];
		cafter = cnt[x].count(y) == 0 ? 0 : cnt[x][y];	
	} else {
		for (int i = 0; i < e[x].size(); ++ i) {
			if (color[e[x][i]] == now) ++ cnow;
			else if (color[e[x][i]] == y) ++ cafter;
		}
		//cout << y << ' ' << color[e[x][0]] << ' ' << now << ' ' << cnow << ' ' << cafter << ' ' << ans << endl;
	}
	ans += cnow - cafter;
	for (int i = 0; i < l[x].size(); ++ i) {
		int u = l[x][i];
		cnt[u][now] --;
		cnt[u][y] ++;
	}
	color[x] = y;
}

int main() {
	cin >> T;
	for (int t = 1; t <= T; ++ t) {
		ans = 1;
		cin >> n;
		for (int i = 0; i < n; ++ i) {
			e[i].clear();
			l[i].clear();
			cnt[i].clear();
			color[i] = 0;
		}
		for (int i = 0; i < n - 1; ++ i) {
			int a, b;
			cin >> a >> b;
			-- a; -- b;
			e[a].push_back(b);
			e[b].push_back(a);
		}

		for (int i = 0; i < n; ++ i) {
			if (e[i].size() >= threshold)
				cnt[i][0] = e[i].size();
			for (int j = 0; j < e[i].size(); ++ j)
				if (e[e[i][j]].size() >= threshold)
					l[i].push_back(j);
		}

		cin >> m;
		printf("Case #%d:\n", t);
		for (int i = 0; i < m; ++ i) {
			int op, x, y;
			cin >> op;
			if (op == 1) {
				printf("%d\n", ans);
			} else if (op == 2) {
				cin >> x >> y;
				-- x;
				change_color(x, y);
			}
		}
	}
    return 0;
}
