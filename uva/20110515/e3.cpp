#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <vector>

using namespace std;
const double eps = 1e-8;

double g[110][110], f, g1, g2, ans[110];
int T, tst;
double M, Y;
double s[10][10];

void solve1() {
	int n = 5*5;
	memset(g, 0, sizeof(g));
	
	for(int a = 0; a <= 4; ++a)
	for(int b = 0; b <= 4; ++b) {
		if(a==4) {
			g[a*5+b][a*5+b] = 1;
			g[a*5+b][n] = 1;
			continue;
		}
		if(b==4) {
			g[a*5+b][a*5+b] = 1;
			continue;
		}
		if(a==3&&b==3)continue;
		
		g[a*5+b][a*5+b] = 1;
		int aa = a+1, bb = b;
		if(aa == 3 && bb == 3) {aa--; bb--;}
		g[a*5+b][aa*5+bb] = -M;
		aa = a; bb = b+1;
		if(aa == 3 && bb == 3) {aa--; bb--;}
		g[a*5+b][aa*5+bb] = -(1.-M);
	}

	for(int a = 0; a <= 4; ++a)
	for(int b = 0; b <= 4; ++b) {
		int r = a*5+b;
		int k = r;
		for(int i = r+1; i < n; ++i)
		if(fabs(g[i][r]) > fabs(g[k][r])) k = i;
		if(fabs(g[k][r]) < eps)continue;
		
		for(int i = 0; i <= n; ++i)
			swap(g[k][i], g[r][i]);
		for(int i = r+1; i < n; ++i)
			if(fabs(g[i][r]) > eps) {
				double t = g[i][r]/g[r][r];
				for(int j = 0; j <= n; ++j)
					g[i][j] -= t * g[r][j];
			}
	}
	
	for(int i = n-1; i >= 0; --i) {
		if(fabs(g[i][i])<eps)continue;
		double res = g[i][n];
		for(int j = i+1; j < n; ++j)
			res -= g[i][j] * ans[j];
		ans[i] = res / g[i][i];
	}
	g1 = ans[0];
}


void solve2() {
	int n = 5*5;
	memset(g, 0, sizeof(g));
	
	for(int a = 0; a <= 4; ++a)
	for(int b = 0; b <= 4; ++b) {
		if(a==4) {
			g[a*5+b][a*5+b] = 1;
			g[a*5+b][n] = 1;
			continue;
		}
		if(b==4) {
			g[a*5+b][a*5+b] = 1;
			continue;
		}
		if(a==3&&b==3)continue;
		
		g[a*5+b][a*5+b] = 1;
		int aa = a+1, bb = b;
		if(aa == 3 && bb == 3) {aa--; bb--;}
		g[a*5+b][aa*5+bb] = -Y;
		aa = a; bb = b+1;
		if(aa == 3 && bb == 3) {aa--; bb--;}
		g[a*5+b][aa*5+bb] = -(1.-Y);
	}
	
	for(int a = 0; a <= 4; ++a)
	for(int b = 0; b <= 4; ++b) {
		int r = a*5+b;
		int k = r;
		for(int i = r+1; i < n; ++i)
		if(fabs(g[i][r]) > fabs(g[k][r])) k = i;
		if(fabs(g[k][r]) < eps)continue;
		
		for(int i = 0; i <= n; ++i)
			swap(g[k][i], g[r][i]);
		for(int i = r+1; i < n; ++i)
			if(fabs(g[i][r]) > eps) {
				double t = g[i][r]/g[r][r];
				for(int j = 0; j <= n; ++j)
					g[i][j] -= t * g[r][j];
			}
	}
	
	for(int i = n-1; i >= 0; --i) {
		if(fabs(g[i][i])<eps)continue;
		double res = g[i][n];
		for(int j = i+1; j < n; ++j)
			res -= g[i][j] * ans[j];
		ans[i] = res / g[i][i];
	}
	g2 = ans[0];
}


void solve3() {
	int n = 7*7;
	memset(g, 0, sizeof(g));
	
	for(int a = 0; a <= 6; ++a)
	for(int b = 0; b <= 6; ++b) {
		if(a==6) {
			g[a*7+b][a*7+b] = 1;
			g[a*7+b][n] = 1;
			continue;
		}
		if(b==6) {
			g[a*7+b][a*7+b] = 1;
			continue;
		}
		if(a==5&&b==5)continue;
		double pp;
		if((a+b)&1) pp = g2;
		else pp = g1;
		
		g[a*7+b][a*7+b] = 1;
		int aa = a+1, bb = b;
		if(aa == 5 && bb == 5) {aa--; bb--;}
		g[a*7+b][aa*7+bb] = -pp;
		aa = a; bb = b+1;
		if(aa == 5 && bb == 5) {aa--; bb--;}
		g[a*7+b][aa*7+bb] = -(1.-pp);
	}
	
	for(int a = 0; a <= 6; ++a)
	for(int b = 0; b <= 6; ++b) {
		int r = a*7+b;
		int k = r;
		for(int i = r+1; i < n; ++i)
		if(fabs(g[i][r]) > fabs(g[k][r])) k = i;
		if(fabs(g[k][r]) < eps)continue;
		
		for(int i = 0; i <= n; ++i)
			swap(g[k][i], g[r][i]);
		for(int i = r+1; i < n; ++i)
			if(fabs(g[i][r]) > eps) {
				double t = g[i][r]/g[r][r];
				for(int j = 0; j <= n; ++j)
					g[i][j] -= t * g[r][j];
			}
	}
	
	for(int i = n-1; i >= 0; --i) {
		if(fabs(g[i][i])<eps)continue;
		double res = g[i][n];
		for(int j = i+1; j < n; ++j)
			res -= g[i][j] * ans[j];
		ans[i] = res / g[i][i];
	}
	f = ans[0];
}

void work()
{
	int x, y;
	scanf("%d%d", &x, &y);
	M = x * 0.01; Y = y * 0.01;

	solve1();
	solve2();
	solve3();
	memset(s, 0, sizeof(s));
	for(int i = 0; i <= 2; ++i) s[3][i] = 1;
	for(int i = 0; i <= 2; ++i)
	for(int j = 0; j <= 2; ++j) s[i][j] = 0.5;
	
	for(int i = 4; i >= 0; --i)
	for(int a = min(2, i); a >= 0; --a) {
		int b = i - a;
		if(b >= 3)continue;
		double pp = f;
		
		s[a][b] = pp * s[a+1][b] + (1.-pp)* s[a][b+1];
	}
	
	printf("%.4f%%\n", s[0][0]*100.); 
}

int main()
{
	freopen("e.in", "r", stdin);
	scanf("%d", &T);
	while(tst < T) {
		printf("Case #%d: ", ++tst);
		work();
	}
	
	return 0;
}

