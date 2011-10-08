#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
#include <queue>

using namespace std;

#define maxn (10000)
#define PB push_back

char buf[100];

struct landmark {
	int x, y;
	
	landmark() {}
	landmark(int a, int b) : x(a), y(b) {}
	
	void GPS() {
		scanf("%s%d%d", buf, &x, &y);
		x *= 4, y *= 4;
		
		for (int i = 0, k = 5120; i < 8; ++i, k >>= 1) {
			int now = buf[i] - '0';
		
			if (now & 2) x += k;
			if (now & 1) y += k;
		}
		
		//printf("%s %d %d\n", buf, x, y);
	}
} g[maxn];

int dist(int a,int b) {
	return (g[a].x - g[b].x) * (g[a].x - g[b].x) + (g[a].y - g[b].y) * (g[a].y - g[b].y);
}

vector<int> walk[maxn], bus[maxn];
int n;
map<string, int> hash;
int dis[maxn];
bool vis[maxn];
queue<int> q;

void relax(int k, vector<int>& e, int v) {
	for (int i = 0; i < e.size(); ++i) {
		int to = e[i];
		
		if (dis[to] == -1 || dis[to] > dis[k] + v) {
			dis[to] = dis[k] + v;
			
			if (!vis[to]) q.push(to), vis[to] = true;
		}
	}
}

bool SPFA(int st, int ed) {
	memset(dis, -1, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	while (!q.empty()) q.pop();
	
	dis[st] = 0, q.push(st), vis[st] = true;
	
	while (!q.empty()) {
		int k = q.front(); q.pop(); vis[k] = false;
		
		relax(k, walk[k], 0); relax(k, bus[k], 1);
	}
	
	if (dis[ed] == -1) return false;
	
	printf("%d\n", dis[ed]);
	return true;
}

void work() {
	g[0].GPS(); g[1].GPS();
	
	walk[0].clear(), walk[1].clear(), bus[0].clear(), bus[1].clear();
	
	scanf("%d", &n); hash.clear();
	for (int i = 1; i <= n; ++i) {
		scanf("%s%d%d", buf, &g[i + 1].x, &g[i + 1]. y);
	
		walk[i + 1].clear(), bus[i + 1].clear();
		//printf("%d %d %d\n", i, dist(0, i + 1), dist(i + 1, 1));
		if (dist(0, i + 1) <= 1000000) walk[0].PB(i + 1);
		if (dist(i + 1, 1) <= 1000000) walk[i + 1].PB(1);
		
		hash[buf] = i + 1;
	}
	
/*
	for (int i = 1; i <= n; ++i) 
		for (int j = i + 1; j <= n; ++j) 
			if (dist(i, j) <= 1000000) walk[i].PB(j), walk[j].PB(i);
*/

	int m; scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		int sum, st, ed; scanf("%d", &sum);
		vector<int> tmp; tmp.clear();
	
		for (int j = 1; j <= sum; ++j) {
			scanf("%s", buf); tmp.PB(hash[buf]);
		}
		
		for (int i = 0; i < sum; ++i)	
			for (int j = i + 1; j < sum; ++j)
				bus[tmp[i]].PB(tmp[j]), bus[tmp[j]].PB(tmp[i]);
	}
	
	if (dist(0, 1) <= 4000000) {
		puts("walk there"); return ;
	}
	
	if (SPFA(0, 1)) return ;
	
	puts("take a taxi"); 
}

int main() {
	int T; scanf("%d", &T);
	
	while (T--) work();

	return 0;
}
