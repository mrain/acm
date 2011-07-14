#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int n, D;
double o1, o2, both, none, ans;
double f[101][101][101];
bool A[101], B[101];

void init() {
	memset(A, 0, sizeof(A));
	memset(B, 0, sizeof(B));
	int p, q;
	scanf("%d", &p);
	for (int i = 0; i < p; ++ i)
		scanf("%d", &q), A[q - 1] = true;
	scanf("%d", &p);
	for (int i = 0; i < p; ++ i)
		scanf("%d", &q), B[q - 1] = true;
	o1 = o2 = both = none = 0;
	for (int i = 0; i < n; ++ i)
		if (A[i]) {
			if (B[i]) ++ both;
			else ++ o1;
		} else if (B[i]) ++ o2;
		else ++ none;
	o1 /= n, o2 /= n, both /= n, none /= n;
	scanf("%d", &D);
}

int main() {
	int ca = 0;
	while (1) {
		scanf("%d", &n);
		if (!n) break;
		init();
		memset(f, 0, sizeof(f));
		f[0][0][0] = 1;
		for (int k = 0; k < D; ++ k)
			for (int i = 0; i <= k; ++ i)
				for (int j = 0; j <= k; ++ j)
					if (f[k][i][j] > 1e-8) {
						f[k + 1][i][j] += f[k][i][j] * none;
						f[k + 1][i + 1][j] += f[k][i][j] * o1;
						f[k + 1][i][j + 1] += f[k][i][j] * o2;
						f[k + 1][i + 1][j + 1] += f[k][i][j] * both;
					}
		ans = 0;
		for (int i = 0; i <= D; ++ i)
			for (int j = 0; j <= D; ++ j)
				if (2 * i == j)
					ans += f[D][i][j];
		if (ans < 1e-6) ans = 0;
		ans = (int)(ans * 100000 + 0.5 + 1e-7);
		ans /= 100000;
		printf("Case %d: %.5f\n", ++ ca, ans);
	}
	return 0;
}

