#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;

vector <int> g[100010];
vector <int> w[100010];
bool vis[100010];

map <string, int> pool;
int tests;
int n, Q, m;
queue<int> q, x;

int reach(int a, int b) {
	while(!q.empty()) q.pop();
	while(!x.empty()) x.pop();
	q.push(a); x.push(0);
	memset(vis, 0, sizeof(vis));
	vis[a] = true;
	while (!q.empty()) {
		int now = q.front(); q.pop();
		int val = x.front(); x.pop();
		for (int i = 0; i < g[now].size(); ++ i) {
			int next = g[now][i];
			if (vis[next]) continue;
			vis[next] = true;
			int nv = val;
			if (next & 1) nv += w[now][i];
			else nv -= w[now][i];
			if (next == b) return nv;
			q.push(next); x.push(nv);
		}
	}
	return -1;
}

int get(const string &a) {
	if (pool.count(a) == 0) {
		int t = pool.size();
		g[2 * t].clear();
		g[2 * t + 1].clear();
		w[2 * t].clear();
		w[2 * t + 1].clear();
		pool.insert(make_pair(a, pool.size()));
	}
	return pool[a];
}

void addedge(int a, int b, int val) {
	g[2 * a].push_back(2 * b + 1);
	w[2 * a].push_back(val);
	g[2 * b].push_back(2 * a + 1);
	w[2 * b].push_back(val);
	g[2 * a + 1].push_back(2 * b);
	w[2 * a + 1].push_back(val);
	g[2 * b + 1].push_back(2 * a);
	w[2 * b + 1].push_back(val);
}

int invalid = 0x3F3F3F3F;

int main() {
	cin >> tests;
	for (int cases = 1; cases <= tests; ++ cases) {
		pool.clear();
		cin >> n;
		for (int ttt = 0; ttt < n; ++ ttt) {
			string sa, sb, str;
			cin >> str;
			int tt = 0;
			for (tt = 0; tt < str.length(); ++ tt) {
				if (str[tt] == '+') break;
				sa += str[tt];
			}
			for (++ tt; tt < str.length(); ++ tt) {
				if (str[tt] == '=') break;
				sb += str[tt];
			}
			int val = 0, mp = 1;
			++ tt;
			if (str[tt] == '-') {
				mp = -1;
				++ tt;
			}
			for (; tt < str.length(); ++ tt) {
				val = val * 10 + (str[tt] - '0');
			}
			int a = get(sa), b = get(sb);
			addedge(a, b, val * mp);
		}
		m = pool.size() * 2;

		cin >> Q;
		cout << "Case #" << cases << ":" << endl;
		for (int ttt = 0; ttt < Q; ++ ttt) {
			string sa, sb, str;
			cin >> str;
			int tt = 0;
			for (tt = 0; tt < str.length(); ++ tt) {
				if (str[tt] == '+') break;
				sa += str[tt];
			}
			for (++ tt; tt < str.length(); ++ tt) {
				if (str[tt] == '=') break;
				sb += str[tt];
			}
			int a = get(sa), b = get(sb);
			
			//if (a < m && b < m && g[a][b] != invalid)
			int r = reach(2 * a, 2 * b + 1);
			if (r != -1)
				cout << sa << "+" << sb << "=" << r << endl;
		}
	}
    return 0;
}
