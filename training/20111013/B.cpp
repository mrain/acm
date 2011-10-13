#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <set>

using namespace std;

#define maxn (17)

int g[2][maxn];
queue<int> q;
int f[(1 << 16) + 5];
vector<int> e[2][maxn][2][maxn];
int n, N;

char buf[100];

void work() {
	scanf("%d", &N);
	
	scanf("%s", buf);
	for (int i = 0; i < N; ++i) g[0][i] = buf[i] - 'A' + 1;
	scanf("%s", buf);
	for (int i = 0; i < N; ++i) g[1][i] = buf[i] - 'A' + 1;
	
	n = N + N; 
	for (int i = 0; i < 2; ++i) 
		for (int j = 0; j < N; ++j) 
			for (int a = i; a < 2; ++a)
				for (int b = j; b < N; ++b) {
					e[i][j][a][b].clear();	
					set<int> p; p.clear();
					
					for (int r = i; r <= a; ++r)
						for (int c = j; c <= b; ++c) 
							p.insert(g[r][c]);
							
					for (set<int>::iterator it = p.begin(); it != p.end(); ++it) {
						int now = *it, v = 0;
						
						for (int r = i; r <= a; ++r)
							for (int c = j; c <= b; ++c) {
								int x = g[r][c] == now ? 1 : 0;
								v |= (x << (r * N + c));
							}
						
						e[i][j][a][b].push_back(v);
						
//						printf("%d %d %d %d : %d\n", i, j, a, b, v);
					}
				}
				
	while (!q.empty()) q.pop();
	memset(f, -1, sizeof(f));
	f[0] = 0, q.push(0);
	
	while (!q.empty()) {
		int X = q.front(); q.pop();	
		
//		printf("f[%d] = %d\n", X, f[X]);
		
		if (X == ((1 << n) - 1)) {
			printf("%d\n", f[X]); break;
		}
		
		for (int i = 0; i < 2; ++i) 
			for (int j = 0; j < N; ++j) 
				for (int a = i; a < 2; ++a)
					for (int b = j; b < N; ++b) {
						int x = X;
						
						if (i == 0) 
							x &= ((1 << n) - 1 - (1 << (b + 1)) + (1 << j));
						
						if (a == 1) 
							x &= ((1 << n) - 1 - (1 << (b + 1 + N)) + (1 << (j + N)));
							
						for (int k = 0; k < e[i][j][a][b].size(); ++k) {
							int v = x | e[i][j][a][b][k];
							
							if (f[v] == -1) f[v] = f[X] + 1, q.push(v);//, printf("%d -> %d, %d %d %d %d\n", X, v, i, j, a, b);
						}
					}
	}
}

int main() {
	int T; scanf("%d", &T);
	
	for (int t = 1; t <= T; ++t) {
		printf("Case #%d: ", t);
		work();
	}

	return 0;
}
