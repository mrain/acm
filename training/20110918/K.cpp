#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (3000)

double F[maxn][5];
double G[maxn][5];
bool vis[maxn][5];
int n, a, b;

inline double g(int x, int y) {
	return x > n ? (y == 3 ? 1. : 0.) : G[x][y];
}

double dfs(int P, int S) {
	if (P > n) return 0.;
	if (vis[P][S]) return F[P][S];
	
	vis[P][S] = true;
	
	double E = 1.;
	double& v = F[P][S]; v = 0.;
	for (int i = a; i <= b; ++i) {
		int p = P + i;
		double x = 1.; 
		
		if (S != 1 && g(p, 1) > 0.) v += (dfs(p, 1) + 1.) * g(p, 1) * E, x -= g(p, 1);
		if (S != 2 && g(p, 2) > 0.) v += (dfs(p, 2) + 1.) * g(p, 2) * E, x -= g(p, 2);
		if (g(p, 3) > 0.) v += (dfs(p, 3) + 1.) * g(p, 3) * E, x -= g(p, 3);
		
		E *= x;
	}
	
	//printf("F[%d][%d] = %f \n", P, S, v);
	return v;
}

void work() {
	scanf("%d%d%d", &n, &a, &b);

	memset(vis, 0, sizeof(vis));
	
	for (int i = 1; i <= n; ++i) 
		for (int j = 0; j < 4; ++j)
			scanf("%lf", &G[i][j]);
	
	printf("%.8f\n", dfs(0, 3));
}

int main() {
	int T; scanf("%d", &T);
	
	while (T--) work();

	return 0;
}
