#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

#define maxn (20000)

vector<int> g[maxn];
int d[maxn], r[maxn], v[maxn];
int f[2][maxn];
int n, m, tot, root;

void init() {
	memset(d, 0, sizeof(d));
	for (int i = 1; i <= n; ++i) g[i].clear();
	for (int i = 1; i <= n; ++i) scanf("%d", &v[i]);
	
	for (int i = 0; i < m; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		g[x].push_back(y), d[y]++;
	}
	
	for (int i = 1; i <= n; ++i) if (d[i] == 0) {
		root = i; break;
	}
/*	
	int top = 0, cnt = 0;
	for (int i = 1; i <= n; ++i) if (d[i] == 0) {
		d[i] = top; top = i;
	}
	
	while (top) {
		int k = top; top = d[k];
		r[++cnt] = k;
		
		for (int i = 0; i < g[k].size(); ++i) {
			int x = g[k][i]; 
			
			if (--d[x] == 0) {
				d[x] = top; top = x;
			}
		}
	}
*/
}

int dfs(int x, int typ) {
	int& ret = f[typ][x];
	if (ret != -1) return ret;
	
	for (int i = 0; i < g[x].size(); ++i) {
		int k = g[x][i];
		
		if (typ == 0) {
			int tmp = dfs(k, 1);
			if (ret == -1 || ret < tmp) ret = tmp;
		}
		else {
			int tmp = dfs(k, 0);
			if (ret == -1 || ret > tmp) ret = tmp;
		}
	}
	
	if (ret < 0) ret = 0;
	ret += v[x];
	
	return ret;
}	 

void work() {
	init();
	
	memset(f, -1, sizeof(f));
	//cout << root << ' ' << dfs(root, 0) << endl;
	puts(dfs(root, 0) < tot ? "Glory" : "Victory");
}

int main() {
	
	while (scanf("%d%d%d", &n, &m, &tot) == 3) work();

	return 0;
}
