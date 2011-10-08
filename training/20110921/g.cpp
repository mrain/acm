#include <cstdio>
#include <set>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <cstdlib>
using namespace std;
#define maxn (1010)
#define A first
#define B second

typedef pair<int, int> PII;
typedef pair<PII, int> PIII;
int n, m, d[maxn];
set<PII> h[maxn];
//set<int> vis;
//vector <int> la, lb, lw, lwa, lwb;
int la[maxn * maxn], lb[maxn * maxn], lw[maxn * maxn], lwa[maxn * maxn], lwb[maxn * maxn], ll;
short int vis[maxn * maxn];
int times, limit;
short int use[maxn];

inline void ins(int i, PII t) {
	if (t.A <= 0) return;
	h[i].insert(t);
	if ((int)h[i].size() > n + 1) h[i].erase(h[i].begin());
}

inline PII top(int i) {
	while (!h[i].empty() && /*vis.count(h[i].rbegin()->B)*/ vis[h[i].rbegin()->B] == times)
		h[i].erase(*h[i].rbegin());
	if (h[i].empty()) return make_pair(-1, -1);
	else return *h[i].rbegin();
}

inline void pop(int i) {
	h[i].erase(*h[i].rbegin());
}

inline bool isempty(int i) {
	while (!h[i].empty() && /*vis.count(h[i].rbegin()->B)*/ vis[h[i].rbegin()->B] == times)
		h[i].erase(*h[i].rbegin());
	return h[i].empty();
}

int main() {
	times = 0;
	while (scanf("%d%d", &n, &m) == 2) {
		++ times;
		//la.clear(); lb.clear(); lw.clear();
		/*lwa.clear(); lwb.clear(); */ ll = 0;
		for (int i = 0; i < n; ++ i) {
			h[i].clear(); d[i] = 0;
		}

		for (int i = 0; i < m; ++ i) {
			int a, b, D, w;
			scanf("%d%d%d%d", &a, &b, &D, &w);
			if (D == 1) d[a] = max(d[a], w);
			else {
				la[ll] = a; lb[ll] = b; lw[ll ++] = w;
			}
		}

		for (int i = 0; i < ll; ++ i) {
			lwa[i] = lw[i] - d[la[i]];
			lwb[i] = lw[i] - d[lb[i]];
			ins(la[i], make_pair(lwa[i], i));
			ins(lb[i], make_pair(lwb[i], i));
		}

		int ans = 0;
		for (int i = 0; i < n; ++ i)
			ans += d[i];

		for (int i = 0; i < n; ++ i) {
			int cur = -1;
			PII now;
			for (int j = 0; j < n; ++ j) {
				if (use[j] == times) continue;
				PII tmp = top(j);
				if (tmp.B != -1 && (cur == -1 || tmp > now))
					cur = j, now = tmp;
			}
			if (cur == -1 || now.A <= 0) break;

			pop(cur); ans += now.A; use[cur] = times;
			int eid = now.B, ea = la[eid], eb = lb[eid], ano;
			int offset;
			if (ea == cur) offset = lwa[eid] - now.A, ano = eb;
			else offset = lwb[eid] - now.A, ano = ea;
			vis[eid] = times;

			while (!isempty(cur)) {
				PII tmp = *h[cur].rbegin(); pop(cur);
				int cost = tmp.A + offset, id = tmp.B;
				if (cost > 0) {
					ins(ano, make_pair(cost, id));
					if (la[id] == cur) la[id] = ano, lwa[id] = cost;
					else lb[id] = ano, lwb[id] = cost;
				}
			}
		}

		printf("%d\n", ans);
	}
	return 0;
}

