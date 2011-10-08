#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define A first
#define B second

typedef map<int, int>::iterator ITER;

map<int, int> f[2];
int n, m, now;
int g[20][20][5][5];
char s[20];

const int mod = 1000000007;

void init() {
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; ++i)	
		for (int j = 1; j <= n; ++j) {
			scanf("%s", s);
			for (int k = 0; k < 4; ++k) 
				g[i][j][0][k] = s[k] == 'C' ? 1 : s[k] == 'R' ? 2 : 3; 
		}
		
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j)
			for (int k = 1; k < 4; ++k)
				for (int a = 0; a < 4; ++a)
					g[i][j][k][a] = g[i][j][0][(a + k) % 4];
}

void change() {
	int to = now ^ 1; f[to].clear();
	
	for (ITER it = f[now].begin(); it != f[now].end(); ++it) {
		int X = it -> A, V = it -> B;
		if (!V) continue;
		
		int& v = f[to][X << 2]; v += V;
		while (v >= mod) v -= mod; 
	}
	
	now = to;
}

void trans(int x, int y) {
	int to = now ^ 1; f[to].clear();
	
	for (ITER it = f[now].begin(); it != f[now].end(); ++it) {
		int X = it -> A, V = it -> B;
		if (!V) continue;
		
		int l = y + y - 2, u = y + y;
		int L = (X >> l) & 3, U = (X >> u) & 3;
		
		for (int i = 0; i < 4; ++i) {
			if (L && g[x][y][i][3] != L) continue;
			if (U && g[x][y][i][0] != U) continue;
			
			int& v = f[to][X + ((g[x][y][i][2] - L) << l) + ((g[x][y][i][1] - U) << u)];
			v += V; while (v >= mod) v -= mod;
		}
	}
	
	now = to;
}

void work() {
	now = 0, f[0].clear(); f[now][0] = 1; 

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) trans(i, j);
		
		if (i < m) change();
	}
}

void calc() {
	int ans = 0;
	
	for (ITER it = f[now].begin(); it != f[now].end(); ++it) {
		ans += it -> B; while (ans >= mod) ans -= mod;
	}
	
	printf("%d\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	
	for (int i = 1; i <= T; ++i) {
		printf("Case %d: ", i);
		
		init(); work(); calc();	
	}

	return 0;
}

