#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (1500)

struct point {
	int x, y;
} g[maxn];

inline bool operator < (point a, point b) {
	return a.x < b.x || a.x == b.x && a.y < b.y;
}

int n;

inline double dist(int a, int b) {
	return sqrt((double)(g[a].x - g[b].x) * (g[a].x - g[b].x) + (g[a].y - g[b].y) * (g[a].y - g[b].y));
}

inline bool cross(int i, int j, int k) {
	return (g[j].x - g[i].x) * (g[k].y - g[i].y) != (g[j].y - g[i].y) * (g[k].x - g[i].x);
}

double calc(int l, int r) {
	if (r - l < 2) return 1e200;
	
	int mid = (l + r) >> 1;
	double ret = min(calc(l, mid), calc(mid + 1, r));
	
	for (int i = l; i <= mid; ++i) 
		for (int j = mid + 1; j <= r; ++j)
			for (int k = j + 1; k <= r; ++k) {
				if (g[k].x + g[j].x - g[i].x - g[i].x > ret) break;
				
				if (cross(i, j, k)) ret = min(ret, dist(i, j) + dist(i, k) + dist(j, k));
			}
			
	for (int i = mid + 1; i <= r; ++i) 
		for (int j = l; j <= mid; ++j)
			for (int k = j + 1; k <= mid; ++k) {
				if (g[i].x + g[i].x - g[j].x - g[k].x > ret) break;
				
				if (cross(i, j, k)) ret = min(ret, dist(i, j) + dist(i, k) + dist(j, k));
			}
			
	return ret;
}

int main() {
	int T; scanf("%d", &T);
	
	for (int t = 1; t <= T; ++t) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d%d", &g[i].x, &g[i].y);
		sort(g + 1, g + 1 + n);
	
		double ans = calc(1, n);
		if (ans < 1e100) printf("Case %d: %.3f\n", t, ans);
		else printf("Case %d: No Solution\n", t);
	}

	return 0;
}
