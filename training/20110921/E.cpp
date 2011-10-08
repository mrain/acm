#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (1000)

int n;
int l[maxn], r[maxn], u[maxn], d[maxn];

const int inf = 10001;

int main() {
	int T; scanf("%d", &T);
	
	while (T--) {
		scanf("%d", &n);
		
		for (int i = 1; i <= n; ++i) scanf("%d%d%d%d", &l[i], &d[i], &r[i], &u[i]);
		
		int ans = 0;
		if (n > 1)
		for (int i = 1; i <= n; ++i) {
			int L = -inf, R = inf, U = inf, D = -inf;
			for (int j = 1; j <= n; ++j) if (j != i) L = max(L, l[j]), R = min(R, r[j]), U = min(U, u[j]), D = max(D, d[j]);
			
			ans = max(ans, max(0, (R - L)) * max(0, (U - D)));
		}		
		
		printf("%d\n", ans);
	}

	return 0;
}
