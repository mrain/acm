#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
#define two(x) (1<<(x))

long long f[two(9)][two(9)];
long long g[10][two(9)];
int n, m;
int times;

inline int get(int st, int pos) {
	return (st >> pos) & 1;
}

void calc(int s) {
	static long long g[10][two(9)];
	memset(g, 0, sizeof(g));
	g[0][0] = 1;
	for (int i = 0; i < m; ++ i)
		for (int t = 0; t < two(m); ++ t) {
			if (!g[i][t]) continue;
			long long val = g[i][t];
			if (get(s, i)) {
				g[i + 1][t] += val;
				continue;
			}
			if (i < m - 1 && !get(s, i + 1)) {
				g[i + 2][t] += val;
				g[i + 2][t | two(i + 1)] += val;
			}

			if (get(t, i)) continue;
			g[i + 1][t | two(i)] += val;
			if (i && !get(t, i - 1)) g[i + 1][t | two(i) | two(i - 1)] += val;
			if (i < m - 1) g[i + 1][t | two(i) | two(i + 1)] += val;
			if (i < m - 1 && !get(s, i + 1))
				g[i + 2][t | two(i)] += val;
		}
	for (int i = 0; i < two(m); ++ i)
		f[s][i] = g[m][i];
}

int main() {
	scanf("%d%d", &n, &m);
	memset(f, 0, sizeof(f));
	for (int i = 0; i < two(m); ++ i) //{
//		dfs(i, 0, 0);
		calc(i);
/*		for (int j = 0; j < two(m); ++ j)
			cout << f[i][j] << ' ';
		cout << endl;
	}*/
	memset(g, 0, sizeof(g));
	g[0][0] = 1;
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < two(m); ++ j) {
			if (!g[i][j]) continue;
			for (int k = 0; k < two(m); ++ k)
				g[i + 1][k] += g[i][j] * f[j][k];
		}
	cout << g[n][0] << endl;
	return 0;
}
