#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <queue>
#define Eps 1e-12
#define INF 1e9
using namespace std;

int n, m;
int a[1010], b[1010], dist[2010];
int head[2010], back[2010], next[200010], v[200010], tot, source, sink;
double f[200010];
queue <int> q;

inline int sgn(double a) {
	return a < -Eps ? -1 : a > Eps ? 1 : 0;
}

bool bfs() {
	while (!q.empty()) q.pop();
	q.push(source);
	memset(dist, 0xFF, sizeof(dist));
	memcpy(head, back, sizeof(back));
	dist[source] = 1;
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (int i = head[now]; i; i = next[i])
			if (f[i] > Eps && dist[v[i]] == -1) {
				dist[v[i]] = dist[now] + 1;
				q.push(v[i]);
			}
	}
	return dist[sink] != -1;
}

double dfs(int now, double capa) {
	double flow = 0;
	if (now == sink) return capa;
	for (int &i = head[now]; i; i = next[i])
		if (dist[v[i]] == dist[now] + 1 && f[i] > Eps) {
			double tmp = dfs(v[i], min(capa - flow, f[i]));
			f[i] -= tmp;
			f[i ^ 1] += tmp;
			flow += tmp;
		}
	if (f[now] < Eps) dist[now] = -1;
	return flow;
}

void addedge(int a, int b, double w) {
	v[tot] = b; next[tot] = back[a]; f[tot] = w; back[a] = tot ++;
	v[tot] = a; next[tot] = back[b]; f[tot] = 0; back[b] = tot ++;
}

bool check(double ans) {
	memset(back, 0, sizeof(back));
	tot = 2;
	for (int i = 0; i < m; ++ i) {
		addedge(i, a[i] + m, INF);
		addedge(i, b[i] + m, INF);
		addedge(source, i, 1.);
	}
	for (int i = 0; i < n; ++ i)
		addedge(i + m, sink, ans);
	double res = m;
	while (bfs())
		 res -= dfs(source, INF);
	return res < Eps;
}

int main() {
	freopen("10", "r", stdin);
	cout.setf(ios::fixed);
	cout.precision(10);
	bool first = true;
	while (scanf("%d%d", &n, &m) == 2) {
		if (!first) cout << endl;
		first = false;
		if (m == 0) {
			cout << 1 << endl << 1 << endl;
			return 0;
		}
		for (int i = 0; i < m; ++ i) {
			scanf("%d%d", &a[i], &b[i]);
			-- a[i]; -- b[i];
		}
		source = n + m; sink = source + 1;
		double low = 0., high = 1000., best = 0.;
		for (int step = 0; step < 70; ++ step) {
			double mid = (low + high) * 0.5;
			if (check(mid)) high = mid;
			else low = mid, best = max(best, mid);
		}
		check(best);
		vector <int> ans;
		for (int i = head[sink]; i; i = next[i]) {
			if (f[i ^ 1] < Eps) ans.push_back(v[i] - m + 1);
			cout << v[i] - m + 1 << ' ' << f[i] << ' ' << f[i ^ 1]  << endl;
		}
		sort(ans.begin(), ans.end());
		/*for (int i = head[source]; i; i = next[i])
			if (f[i] > Eps) ans.push_back(a[i] + 1), ans.push_back(b[i] + 1);*/
		sort(ans.begin(), ans.end());
		ans.erase(unique(ans.begin(), ans.end()), ans.end());
		cout << ans.size() << endl;
		for (int i = 0; i < (int)ans.size(); ++ i)
			cout << ans[i] << endl;
	}
	return 0;
}
