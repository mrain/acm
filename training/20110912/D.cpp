#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define maxn (110)
#define maxm (20)
#define A first
#define B second
#define MP make_pair

typedef pair<int, int> PII;
typedef pair<PII, int> PIII; 

int dis[maxn][maxn][maxm];
int g[maxn][maxn], typ[maxn][maxn];
queue<PIII> q;
int m, n;
PII st;
char buf[1000];

const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

void calc(int x, int y, char v) {
	if (v == 'B') g[x][y] = 0, typ[x][y] = 1;
	if (v == 'Y') g[x][y] = 1, typ[x][y] = 1;
	if (v == 'R') g[x][y] = 2, typ[x][y] = 1;
	if (v == 'G') g[x][y] = 3, typ[x][y] = 1;
	
	if (v == 'b') g[x][y] = 0, typ[x][y] = 2;
	if (v == 'y') g[x][y] = 1, typ[x][y] = 2;
	if (v == 'r') g[x][y] = 2, typ[x][y] = 2;
	if (v == 'g') g[x][y] = 3, typ[x][y] = 2;
	
	if (v == '*') typ[x][y] = 0, st = MP(x, y);
	if (v == 'X') typ[x][y] = 3;
	
	if (v == '.') typ[x][y] = 0;
	if (v == '#') typ[x][y] = -1;
	
	//printf("%d %d : %d %d\n", x, y, typ[x][y], g[x][y]);
}

void work() {
	while (!q.empty()) q.pop();
	memset(dis, -1, sizeof(dis));
	memset(typ, 0, sizeof(typ));
	memset(g, 0 ,sizeof(g));
	
	for (int i = 0; i <= m + 1; ++i)
		for (int j = 0; j <= n + 1; ++j)
			typ[i][j] = -1;
	
	for (int i = 0; i < m; ++i) {
		scanf("%s", buf);
		for (int j = 0; j < n; ++j)	calc(i + 1, j + 1, buf[j]);
	}
	
	q.push(MP(st, 0)), dis[st.A][st.B][0] = 0;
	while (!q.empty()) {
		PIII now = q.front(); q.pop();
		int X = now.A.A, Y = now.A.B, K = now.B;
		
		//printf("DIS[%d][%d][%d] = %d, %d\n", X, Y, K, dis[X][Y][K], typ[X][Y]);
		
		if (typ[X][Y] == 3) {
			printf("Escape possible in %d steps.\n", dis[X][Y][K]);
			return ;
		}
		
		for (int i = 0; i < 4; ++i) {
			int x = dx[i] + X, y = dy[i] + Y, k = K;
			
			if (typ[x][y] == -1) continue;
			if (typ[x][y] == 1 && (k & (1 << g[x][y])) == 0) continue;
			if (typ[x][y] == 2) k |= (1 << g[x][y]);
			
			if (dis[x][y][k] != -1) continue;
			dis[x][y][k] = dis[X][Y][K] + 1, q.push(MP(MP(x, y), k));
		}
		
	}
	
	puts("The poor student is trapped!");
}

int main() {
	while (scanf("%d%d", &m, &n) == 2 && (m || n)) work();
	
	return 0;
}

/*
Sample Input 

1 10 
*........X 

1 3 
*#X 

3 20 
#################### 
#XY.gBr.*.Rb.G.GG.y# 
#################### 

0 0

Sample Output 

Escape possible in 9 steps. 
The poor student is trapped! 
Escape possible in 45 steps.
*/
