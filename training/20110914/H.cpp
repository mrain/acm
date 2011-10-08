#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

#define maxn (30)
#define MP make_pair
#define A first
#define B second

typedef pair<int, int> PII;
typedef pair<int, PII> PIV;

int g[maxn][maxn];
bool dis[410][25][25];
int M, N, D, Bi, Bs;
PII st;
queue<PIV> q;
char buf[100];
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

void work() {
	memset(g, 0, sizeof(g));

	scanf("%d%d", &M, &N);
	for (int i = 1; i <= M; ++i) {
		scanf("%s", buf);
		for (int j = 1; j <= N; ++j) {
			char x = buf[j - 1];
			
			if (x == 'S') st = MP(i, j);
			if (x == 'E') g[i][j] = 2;
			if (x == '#') g[i][j] = -1;
			if (x == '*') g[i][j] = 1;
		}
	}
	
	scanf("%d%d%d", &D, &Bi, &Bs);
	
	memset(dis, -1, sizeof(dis));
	while (!q.empty()) q.pop();
	
	dis[0][st.A][st.B] = 0, q.push(MP(0, MP(st.A, st.B)));
	
	while (!q.empty()) {
		PIV now = q.front(); q.pop();
		
		int X = now.B.A, Y = now.B.B, T = now.A;
		if (T * Bs >= Bi) continue;
		
		if (g[X][Y] == 2) {
			printf("%d\n", dis[T][X][Y]);
			return ;
		}
		
		for (int i = 0; i < 4; ++i) {
			int x = X + dx[i], y = Y + dy[i], t = T;
			
			if (g[x][y] == -1 || g[x][y] == 1) continue;
			if (dis[t][x][y] != -1) continue;
			
			//dis[t][x][y] = dis[T][X][Y] + 1, q.push(MP(t, x, y));
		}
		
		
	}
	
	puts("can not reach!");
}

int main() {
	int T; scanf("%d", &T);
	
	while (T--) work();

	return 0;
}
