#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (30)

bool vis[maxn];
double l[maxn], a[maxn], b[maxn];
int n, m;
double ans;

inline double SQR(double x) {
	return x * x;
}

void dfs(int x, int sum, double v) {
	if (sum >= m) {
		ans = max(ans, v); return ;
	}
	
	if (x >= n) return ;
	
	dfs(x + 1, sum, v);
	
	vis[x] = true;
	for (int i = 0; i < x; ++i) 
		if (vis[i]) v += SQR(l[x] - l[i]) + SQR(a[x] - a[i]) + SQR(b[x] - b[i]);
	dfs(x + 1, sum + 1, v);
	vis[x] = false;
}

int main() {
	cout.setf(ios::fixed);
	cout.precision(8);
	cin >> n >> m;
	for (int i = 0; i < n; ++i) cin >> l[i] >> a[i] >> b[i];
	
	dfs(0, 0, 0.);
	
	cout << ans << endl;

	return 0;
}
