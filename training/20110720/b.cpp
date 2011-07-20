#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

typedef pair<int, int> PII;
int n, m, r, q;
vector <PII> l[10010];

int calc(const vector<PII> &l, int a, int b) {
	int cnt = 0, ret = 0;
	for (int i = 0; i < (int)l.size(); ++ i) {
		if (cnt) {
			int st = max(l[i - 1].first, a), ed = min(l[i].first, b);
			ret += max(0, ed - st);
		}
		cnt += l[i].second;
	}
	return ret;
}

int main() {
	while (scanf("%d%d", &n, &m) == 2 && n && m) {
		for (int i = 0; i < m; ++ i) l[i].clear();
		scanf("%d", &r);
		for (int i = 0; i < r; ++ i) {
			int t, p, q, s;
			scanf("%d%d%d%d", &t, &p, &q, &s);
			if (!s) s = -1;
			l[q].push_back(make_pair(t, s));
		}
		scanf("%d", &q);
		for (int i = 0; i < q; ++ i) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			printf("%d\n", calc(l[c], a, b));
		}
	}
	return 0;
}

