#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (200)
#define maxm (55)

//const int bound = 50;

double C[maxn][maxm][maxm], S[maxn][maxm][maxm];
int n, m, l;
int p[maxn], t[maxn], v[maxn];
double ans[maxn];

void ready(int x) {
	C[x][0][0] = 1.;
	double P = (double)p[x] / 100.;
	
	for (int i = 1; i <= m; ++i) {
		C[x][i][0] = C[x][i - 1][0] * (1 - P);
		for (int j = 1; j <= i; ++j) C[x][i][j] = C[x][i - 1][j - 1] * P + C[x][i - 1][j] * (1 - P);
	}
	
	for (int i = 0; i <= m; ++i)
		for (int j = m; j >= 0; --j)
			S[x][i][j] = S[x][i][j + 1] + C[x][i][j];
/*			
	for (int i = 0; i <= 5; ++i) {
		for (int j = 0; j <= i; ++j) printf("%f ", S[i][j]);
		puts("");
	}
*/
}

struct rational {
	int a, b;
	
	rational() {}
	rational(int x, int y) : a(x), b(y) {}
	
	void add(int x) {
		a += x * b;
	}
	
	int times(int x) {
		if (a < 0) return 0;
		if (x == 0) return m + 1;
	
		return a / (b * x) + 1;
	}
};

rational subtract(rational x, rational y) {
	return rational(x.a * y.b - x.b * y.a, x.b * y.b);
}



int main() {
	scanf("%d%d%d", &n, &m, &l);
	
	for (int i = 1; i <= n; ++i) scanf("%d%d%d", &p[i], &t[i], &v[i]);
	
	for (int i = 1; i <= n; ++i) ready(i);
	
	for (int i = 1; i <= n; ++i) if (v[i]) {
		rational A(l, v[i]);
	
		for (int j = 0; j <= m; ++j) {
			double now = C[i][m][j];
			
			for (int k = 0; k <= n; ++k) if (now > 0. && v[k] && i != k) {
				rational B(l, v[k]);
				B = subtract(A, B);
				
				int x = B.times(t[k]); x = max(x, 0);
				
				//printf("(%d, %d) : %d, %d : %d / %d\n", i, j, k, x, B.a, B.b);
				
				if (x <= m) now *= S[k][m][x];
				else now = 0.;
			}
			
			
			//printf("%d %d %f\n", i, j, now);
			ans[i] += now;
			
			A.add(t[i]);
		}
	}
	
	for (int i = 1; i <= n; ++i) printf("%.10f\n", ans[i]);

	return 0;
}
