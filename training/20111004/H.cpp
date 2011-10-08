#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define maxn (60000)
#define PB push_back

int cov[maxn * 16];
int ans[15];
vector<int> Q[maxn];
int n, m, q;

char buf[20];

void build(int x, int l, int r) {
	cov[x] = 0;
	
	if (l == r) return ;
	
	int mid = (l + r) >> 1;
	build(x + x, l, mid), build(x + x + 1, mid + 1, r);
}

void cover(int x, int l, int r, int p, int q, int c) {
	//printf("%d %d %d %d %d\n", x, l, r, p, q);

	if (l == p && r == q) {
		cov[x] = c; return ;
	}
	
	if (cov[x]) {
		cov[x + x] = cov[x], cov[x + x + 1] = cov[x]; cov[x] = 0;
	}
	
	int mid = (l + r) >> 1;
	
	if (q <= mid) cover(x + x, l, mid, p, q, c);
	else {
		if (p > mid) cover(x + x + 1, mid + 1, r, p, q, c); 
		else {
			cover(x + x, l, mid, p, mid, c), cover(x + x + 1, mid + 1, r, mid + 1, q, c);
		}
	}
}

void calc(int x, int l, int r) {
	if (l == r) {
		//printf("%d", cov[x]);
	
		ans[cov[x]]++; return ;
	}
	
	if (cov[x]) {
		cov[x + x] = cov[x], cov[x + x + 1] = cov[x];
	}
	
	int mid = (l + r) >> 1;
	calc(x + x, l, mid), calc(x + x + 1, mid + 1, r);
}

void work() {
	for (int i = 0; i < q; ++i) {
		Q[i].clear(); scanf("%s", buf);
		
		if (buf[0] == 'C') {
			Q[i].PB(0); 
			int xc, yc, r, c; scanf("%d%d%d%d", &xc, &yc, &r, &c); xc++, yc++;
			Q[i].PB(xc), Q[i].PB(yc), Q[i].PB(r), Q[i].PB(c);
		}
		if (buf[0] == 'D') {
			Q[i].PB(1); 
			int xc, yc, r, c; scanf("%d%d%d%d", &xc, &yc, &r, &c); xc++, yc++;
			Q[i].PB(xc), Q[i].PB(yc), Q[i].PB(r), Q[i].PB(c);
		}
		if (buf[0] == 'R') {
			Q[i].PB(2); 
			int xc, yc, l, w, c; scanf("%d%d%d%d%d", &xc, &yc, &l, &w, &c); xc++, yc++;
			Q[i].PB(xc), Q[i].PB(yc), Q[i].PB(l), Q[i].PB(w), Q[i].PB(c);
		}
		if (buf[0] == 'T') {
			Q[i].PB(3); 
			int xc, yc, r, c; scanf("%d%d%d%d", &xc, &yc, &r, &c); xc++, yc++, r /= 2;
			Q[i].PB(xc), Q[i].PB(yc), Q[i].PB(r), Q[i].PB(c);
		} 
	}
/*	
	for (int i = 0; i < q; ++i) {
		for (int j = 0; j < Q[i].size(); ++j) printf("%d ", Q[i][j]); puts("");
	}
*/	
	memset(ans, 0, sizeof(ans));
	for (int x = 1; x <= m; ++x) {
		build(1, 1, n);
	
		for (int i = 0; i < q; ++i) {
			int a, b, c;
		
			if (Q[i][0] == 0) {
				int xc = Q[i][1], yc = Q[i][2], r = Q[i][3]; c = Q[i][4];
				
				double lam = (double)r * (double)r - (double)(x - xc) * (double)(x - xc) + 1e-6;
				if (lam < 0) continue;
				int d = (int) sqrt(lam);
				a = yc - d, b = yc + d;
			}
			
			if (Q[i][0] == 1) {
				int xc = Q[i][1], yc = Q[i][2], r = Q[i][3]; c = Q[i][4];
				
				int d = r - abs(x - xc);
				a = yc - d, b = yc + d;
			}
			
			if (Q[i][0] == 2) {
				int xc = Q[i][1], yc = Q[i][2], l = Q[i][3], w = Q[i][4]; c = Q[i][5];
				
				if (x < xc || x >= xc + l) continue;
				a = yc, b = yc + w - 1;
			}
			
			if (Q[i][0] == 3) {
				int xc = Q[i][1], yc = Q[i][2], r = Q[i][3]; c = Q[i][4];
				
				if (x < xc) continue;
				int d = r - abs(x - xc);
				a = yc - d, b = yc + d;
			}
			
			if (a > b) continue;
			a = max(a, 1), b = min(b, n);
			//printf("%d, %d: %d %d %d\n", x, i, a, b, c);
			cover(1, 1, n, a, b, c);
		}
		
		calc(1, 1, n); 
		//puts("");
	}
	
	for (int i = 1; i < 9; ++i) printf("%d ",ans[i]);
	printf("%d\n", ans[9]);
}

int main() {
	while (scanf("%d%d%d", &m, &n, &q) == 3) work();

	return 0;
}
