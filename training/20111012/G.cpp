#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

#define maxn (100000)

typedef pair<int, int> PII;

vector<int> g[maxn];
bool vis[maxn];
multiset<PII> f;
int n, m, cnt1, cnt2;

void dfs(int x) {
	vis[x] = true, cnt1++;
	
	for (int i = 0; i < g[x].size(); ++i) {
		cnt2++;
		int k = g[x][i]; if (vis[k]) continue;
		dfs(k);	
	}
}

bool work() {
	f.clear();
	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) g[i].clear();
	for (int i = 0; i < m; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		g[x].push_back(y), g[y].push_back(x);
	}
	
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; ++i) if (!vis[i]) {
		cnt1 = cnt2 = 0; dfs(i);
		f.insert(make_pair(cnt1, cnt2));
	}
	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) g[i].clear();
	for (int i = 0; i < m; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		g[x].push_back(y), g[y].push_back(x);
	}
	
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; ++i) if (!vis[i]) {
		cnt1 = cnt2 = 0; dfs(i);
		
		multiset<PII>::iterator it = f.find(make_pair(cnt1, cnt2));
		if (it == f.end()) return false;
		f.erase(it);
	}

	return f.empty();
}

int main() {
	int T; scanf("%d", &T);
	
	for (int t = 1; t <= T; ++t) printf("Case #%d: %s\n", t, work() ? "YES" : "NO");

	return 0;
}
