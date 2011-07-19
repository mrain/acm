#include <cstdio>
#include <deque>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

#define maxn (100000)
#define PB push_back

typedef long long LL;

struct path{
	LL data;
	int ed;
	
	path() {}
	path(int a, LL b) : data(b), ed(a) {}
};

vector<int> cycle[maxn], tree;
vector <LL> s[maxn];
vector<path> E[maxn];
int cyclesum, n, m, now;
LL F[2][maxn];
int D[maxn];
bool vis[maxn];

void update(LL& x, const LL& v) {
	if (x < v) x = v;
}

void topuSort() {
	memset(D,0,sizeof(D));
	
	for (int i = 1; i <= n; ++i) ++D[E[i][0].ed];
	
	int top = 0;
	for (int i = 1; i <= n; ++i) if (!D[i]) {
		D[i] = top; top = i;
	}
	
	while (top) {
		int i = top; top = D[top];
		tree.PB(i), vis[i]=true;
		
		int k=E[i][0].ed;
		
		if (!(--D[k])) {
			D[k] = top; top = k;
		}
	}
}

void findCycle(int x) {
	int sum = 0;
	
	while (!vis[x]) {
		cycle[cyclesum].PB(x), vis[x]=true, ++sum;
		
		x = E[x][0].ed;
	}
	
	for (int i = 0; i < sum; ++i) cycle[cyclesum].PB(cycle[cyclesum][i]);
	
	++cyclesum;
}

void init() {
	scanf("%d%d", &n, &m);
	
	for (int i = 1; i <= n; ++i) {
		int sum; scanf("%d", &sum);
		
		for (int j = 0; j < sum; ++j) {
			int x,y; scanf("%d%d", &x, &y);
			E[i].PB(path(x, y));
		}
	}
	
	topuSort();
	
	for (int i = 1; i <= n; ++i) if (!vis[i]) findCycle(i);
}

void DP_tree() {
	for (int i = 0; i < tree.size(); ++i) {
		int k = tree[i]; if (F[now][k] == -1) continue;
		
		int x = E[k][0].ed;
		LL v = E[k][0].data; 
		update(F[now][x], F[now][k] + v);
	}
}

void DP_next() {
	int t = now ^ 1; memset(F[t], -1, sizeof(F[t]));

	for (int i = 1; i <= n; ++i) {
		if (F[now][i] == -1) continue;
		 
		for (int j = 1; j < E[i].size(); ++j) {
			int x = E[i][j].ed;
			LL v = E[i][j].data;
			
			update(F[t][x], F[now][i] + v);
		}	
	}
	
	now = t;
}

void cycle_prepare(const vector<int> &cir, vector<LL> &s) {
	LL now = 0;
	for (int i = 0; i < (int)cir.size(); ++ i) {
		s.push_back(now);
		now += E[cir[i]][0].data;
	}
}

void DP_cycle(const vector<int> &cir, LL *res, const vector<LL> &s) {
	static vector<LL> f;
	static deque<pair<LL, int> > q;
	int n = cir.size() / 2;
	f.clear(); while (!q.empty()) q.pop_back();
	f.resize(cir.size());
	for (int i = 0; i < n; ++ i) {
		f[i] = res[cir[i]];
		if (f[i] == -1) continue;
		while (q.size() && q.back().first < f[i] - s[i]) q.pop_back();
		q.push_back(make_pair(f[i] - s[i], i));
	}
	for (int i = n; i < n + n; ++ i) {
		while (q.size() && q.front().second + n <= i) q.pop_front();
		//f[i] = q.front().first + s[i];
		f[i] = f[i - n];
		if (q.size()) f[i] = max(f[i], q.front().first + s[i]);
		if (f[i - n] == -1) continue;
		while (q.size() && q.back().first < f[i - n] - s[i]) q.pop_back();
		q.push_back(make_pair(f[i - n] - s[i], i));
	}
	for (int i = n; i < n + n; ++ i)
		update(res[cir[i]], f[i]);
}

void work() {
	init();
	now = 0; memset(F[now], -1, sizeof(F[now])); F[now][1] = 0;
	for (int i = 0; i < cyclesum; ++ i)
		cycle_prepare(cycle[i], s[i]);
	
	LL ans = -1;
	for (int i = 0; i < m; ++i) {
/*			
		cout << "======" << i << "======" << endl;
		for (int j = 1; j <= n; ++ j)
			cout << j << ' ' << F[now][j] << endl;
*/			
		DP_tree();
/*		
		cout << "======" << i << "======" << endl;
		for (int j = 1; j <= n; ++ j)
			cout << j << ' ' << F[now][j] << endl;
*/		
		for (int j = 0; j < cyclesum; ++j) DP_cycle(cycle[j], F[now], s[j]);
/*
		cout << "======" << i << "======" << endl;
		for (int j = 1; j <= n; ++ j)
			cout << j << ' ' << F[now][j] << endl;
*/			
		DP_next();
		
		if (F[now][n] != -1) update(ans, F[now][n]);
		//cout << i << ' ' << F[now][n] << endl;
	}
/*
		cout << "======" << m << "======" << endl;
		for (int j = 1; j <= n; ++ j)
			cout << j << ' ' << F[now][j] << endl;
*/	
	DP_tree();
	for (int j = 0; j < cyclesum; ++j) DP_cycle(cycle[j], F[now], s[j]);
	if (F[now][n] != -1) update(ans, F[now][n]);

	//printf("%d\n", ans);
	cout << ans << endl;
}

int main(){
	work();

	return 0;
}
