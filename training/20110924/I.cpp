#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

#define maxn (10000)
#define PB push_back
#define MP make_pair
#define A first
#define B second

typedef pair<int, int> PII;
typedef pair<PII, int> PIII;

vector<PIII> F[maxn];
vector<PIII> Stack;
int tot;

void DFS(int x, int y, int X, int Y) {
	if (x > 4) {
		if (!(X + Y)) F[tot++] = Stack;
		
		return ;
	}

	if (y > 2) {
		DFS(x + 1, 0, X, Y); return ;
	}

	DFS(x, y + 1, X, Y);

	if (x + y) {
		for (int i = 1; ; ++i) {
			if (X < x * i || Y < y * i) break;
			
			Stack.PB(MP(MP(x, y), i));
			DFS(x, y + 1, X - x * i, Y - y * i);
			Stack.pop_back();
		}
	}
}

vector<int> C[10][10][maxn];
int cnt[10][10], used[10][10];
char G[maxn];
vector<int> E[maxn];
vector<int> TMP;
PII now;
int n;
bool vis[maxn];

void dfs(int x) {
	vis[x] = true, TMP.PB(x);
	 
	if (G[x - 1] == '0') now.B++;
	else now.A++;
	
	for (int i = 0; i < E[x].size(); ++i) {
		int k = E[x][i]; if (vis[k]) continue;
		dfs(k);
	}
}

int main() {
	DFS(0, 0, 4, 2);
/*	
	printf("%d\n", tot);
	for (int i = 0; i < tot; ++i) {
		for (int j = 0; j < F[i].size(); ++j) printf("(%d, %d -> %d), ", F[i][j].A.A, F[i][j].A.B, F[i][j].B);
		puts("");
	}
*/
	scanf("%d", &n); n *= 6;
	scanf("%s", G);
	int m; scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		E[x].PB(y), E[y].PB(x);
	}
	
	for (int i = 1; i <= n; ++i) if (!vis[i]) {
		now = MP(0, 0), TMP.clear();
		dfs(i);
/*		
		printf("%d %d:\n", now.A, now.B);
		for (int j = 0; j < TMP.size(); ++j) printf("%d ", TMP[j]);
		puts("");
*/		
		int k = cnt[now.A][now.B]++;
		for (int j = 0; j < TMP.size(); ++j) C[now.A][now.B][k].PB(TMP[j]);
	}
	
	for (int i = 0; i < tot; ++i) {
		while (true) {
			bool flag = true;
			
			for (int j = 0; j < F[i].size(); ++j) {
				int x = F[i][j].A.A, y = F[i][j].A.B, s = F[i][j].B;
				
				if (used[x][y] + s > cnt[x][y]) flag = false;
			}
			
			if (!flag) break;
			
			int num = 0;
			for (int j = 0; j < F[i].size(); ++j) {
				int x = F[i][j].A.A, y = F[i][j].A.B, s = F[i][j].B, to = used[x][y] + s;
				
				for (int k = used[x][y]; k < to; ++k) {
					vector<int>& v = C[x][y][k];
				
					for (int a = 0; a < v.size(); ++a) {
						if (num++) putchar(' '); 
						printf("%d", v[a]);
					}
				}
				
				used[x][y] = to;
			}
			
			puts("");
		}
	}

	return 0;
}
