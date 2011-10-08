#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (1005)

int F[maxn][maxn];
int g[maxn], a[maxn], b[maxn];
char buf[10];
int n, m, k;

int f(int i, int j, int s) {
	int& v = F[i][j];
	
	if (v > -1) return v;
	
	if (i >= m || j >= n) return v = 0;
	
	if (s == 3 && a[i] + b[j] == 0) {
		if (a[i] < 0) g[-a[i]] = 1;
		else g[a[i]] = 0;
	
		//s = 0;	
	} else {
		if (s & 1) {
			if (a[i] < 0) g[-a[i]] = -1;
			else g[a[i]] = 0;
		}
		if (s & 2) {
			if (b[j] < 0) g[-b[j]] = -1;
			else g[b[j]] = 1;
		}
	}
	
	v = 0;
/*	
	if (i < m && j < n && a[i + 1] > 0 && b[j + 1] > 0 && g[a[i + 1]] == 1 && g[b[i + 1]] == 0) v = 1;
	
	if (!v && i < m) {
		if (!(a[i + 1] > 0 && g[a[i + 1]] == 1) && f(i + 1, j, 1)) v = 1;
	}
	
	if (!v && j < n) {
		if (!(b[j + 1] > 0 && g[b[j + 1]] == 0) && f(i, j + 1, 2)) v = 1;
	}
*/
	if (i < m && j < n && a[i + 1] > 0 && b[j + 1] > 0 && g[a[i + 1]] == 1 && g[b[i + 1]] == 0) v = 1;

	bool A = i < m && !(a[i + 1] > 0 && g[a[i + 1]] == 1), B = j < n && !(b[j + 1] > 0 && g[b[j + 1]] == 0);
	
	if (!v && A && !B && f(i + 1, j, 1)) v = 1;
	if (!v && !A && B && f(i, j + 1, 2)) v = 1;
	if (!v && A && B && f(i + 1, j + 1, 3)) v = 1;
	if (!v && i < m && j < n && a[i + 1] + b[j + 1] == 0 && f(i + 1, j + 1, 3)) v = 1; 
	
	
	if (s == 3 && a[i] + b[j] == 0) {
		if (a[i] < 0) g[-a[i]] = 0;
		else g[a[i]] = 1;
	} else {
		if (s & 1) {
			if (a[i] < 0) g[-a[i]] = 0;
			else g[a[i]] = -1;
		}
		if (s & 2) {
			if (b[j] < 0) g[-b[j]] = 1;
			else g[b[j]] = -1;
		}
	}
	
	//printf("F[%d][%d] = %d\n", i, j, v);
	
	return v;
}

int main() {
	int T; scanf("%d", &T);
	
	while (T--) {
		scanf("%d%d%d", &m, &n, &k);
		memset(F, -1, sizeof(F));
		memset(g, -1, sizeof(g));
		
		for (int i = 1; i <= m; ++i) {
			int x; scanf("%s%d", buf, &x);
			a[i] = buf[0] == '+' ? x : -x;		
		}
		
		for (int i = 1; i <= n; ++i) {
			int x; scanf("%s%d", buf, &x);
			b[i] = buf[0] == '+' ? x : -x;		
		}
		
		int ans = f(0, 0, 0);
		if (ans) puts(":-(");
		else puts(":-)");
	}

	return 0;
}
