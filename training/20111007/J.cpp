#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

#define maxn (200000)

struct ele {
	int d, t;
} g[maxn];

bool cmp(ele a, ele b) {
	return b.t < a.t || b.t == a.t && a.d < b.d;
}

int n;

int main() {
	int T; scanf("%d", &T);
	
	for (int t = 1; t <= T; ++t) {
		scanf("%d", &n); 
		for (int i = 1; i <= n; ++i) scanf("%d%d", &g[i].d, &g[i].t);
		sort(g + 1, g + 1 + n, cmp);
		
		int tot = 0, ans = 0;
		for (int i = 1; i <= n; ++i) {
			tot += g[i].d; ans = max(ans, tot + g[i].t);
		}
		
		printf("Case %d: %d\n", t, ans);
	}

	return 0;
}
