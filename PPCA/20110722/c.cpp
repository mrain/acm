#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

inline int min(int a, int b) { return a < b ? a : b; }

int f[3001][3001], l[3001][3001];
int x[3001], y[3001], n;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d", &x[i]);
	for (int i = 0; i < n; ++ i) scanf("%d", &y[i]);
	memset(f, 0x1F, sizeof(f));
	for (int i = 0; i < n; ++ i)
		f[i][i] = 0, l[i][i] = i;
	for (int d = 1; d < n; ++ d)
		for (int i = 0; i + d < n; ++ i) {
			int j = i + d;
			int st = l[i][j - 1], ed = min(l[i + 1][j], j - 1);
			for (int k = st; k <= ed; ++ k) {
				int tmp = f[i][k] + f[k + 1][j] + x[k + 1] - x[i] + y[k] - y[j];
				if (tmp < f[i][j]) {
					f[i][j] = tmp;
					l[i][j] = k;
				}
			}
//			cout << i << ' ' << j << ' ' << f[i][j] << endl;
		}
	printf("%d\n", f[0][n - 1]);
	return 0;
}

