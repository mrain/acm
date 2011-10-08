#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

int n;

int main() {
	int T; scanf("%d", &T);
	
	for (int t = 1; t <= T; ++t) {
		scanf("%d", &n); 
		int x, tot; scanf("%d", &x); tot = x;
		for (int i = 1; i < n; ++i) {
			int v; scanf("%d", &v);
			/*x = min(x, v); */tot += v;
		}

		printf("Case %d: %.6f\n", t, (double) x / (double) tot);
	}

	return 0;
}
