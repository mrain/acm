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

int tests, n, ca, cb;
string a[1010], b[1010];
int g[1010][1010], match[1010];
bool vis[1010];
map <string, int> dicta, dictb;

bool augment(int u) {
	for (int v = 0; v < cb; ++ v) {
		if (g[u][v] == 0) continue;
		if (vis[v]) continue;
		vis[v] = true;
		if (match[v] == -1 || augment(match[v])) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

int main() {
	cin >> tests;
	for (int cases = 1; cases <= tests; ++ cases) {
		cin >> n;
		memset(g, 0, sizeof(g));
		dicta.clear();
		dictb.clear();
		for (int i = 0; i < n; ++ i) {
			int sa, sb;
			cin >> a[i] >> b[i];
			if (dicta.count(a[i]) > 0) {
				sa = dicta[a[i]];
			} else {
				sa = dicta.size();
				dicta[a[i]] = sa;
			}
			if (dictb.count(b[i]) > 0) {
				sb = dictb[b[i]];
			} else {
				sb = dictb.size();
				dictb[b[i]] = sb;
			}
			g[sa][sb] = 1;
		}
		ca = dicta.size(), cb = dictb.size();
		//cout << ca << ' ' << cb << endl;
		int m = 0;
		memset(match, -1, sizeof(match));
		for (int i = 0; i < ca; ++ i) {
			//if (match[i] == -1) {
			memset(vis, 0, sizeof(vis));
			if (augment(i)) ++ m;
			//}
		}
		int ans = n - (ca + cb - m);
		printf("Case #%d: %d\n", cases, ans);
	}
    return 0;
}
