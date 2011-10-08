#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define maxn (300010)
#define maxm (30)

const int bound = 200000;

double f[2][maxn];
int g[maxm];
vector<int> fac[maxn];
int n;

inline void update(double& x, double v) {
	if (x < 0. || x > v) x = v;
}

int main() {
	for (int i = 1; i <= bound; ++i) {
		int x = (int) (sqrt(i) + 1e-5);
		for (int k = 1; k <= x; ++ k) if (i % k == 0) {
			fac[i].push_back(k);
			if (k * k != i) fac[i].push_back(i / k);
		}
	}
//	return 0;
	scanf("%d", &n);
	
	for (int i = 1; i <= n; ++i) scanf("%d", &g[i]);
	

	
	int now = 0;
	for (int i = 1; i <= n; ++i) {
		int to = now ^ 1;
		
		for (int j = 1; j <= bound; ++j) {
			double opt = -1., x = ((double) abs(g[i] - j)) / ((double) g[i]);
			
			for (int k = 0; k < fac[j].size(); ++ k)
				update(opt, max(f[now][fac[j][k]], x));
				
			f[to][j] = opt;
		}
		
		now = to;
	}
	
	double ans = -1.;
	for (int i = 1; i <= bound; ++i) update(ans, f[now][i]);
	printf("%.10f\n", ans);	

	return 0;
}
