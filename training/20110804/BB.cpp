#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;
/*
#define maxn (110)

double f[maxn][maxn];

double calc(int m,int n) {
	memset(f,0,sizeof(f));
	f[0][0]=1.;
	
	double ret=1.;
	
	for (int i=0;i<=m;i++)
		for (int j=0;j<=n;j++) if (f[i][j]>0.) {
			if (i<j) {
				ret-=f[i][j]; continue;
			}
			
			if (i==m&&j==n) continue;
			
			double x=((double)(m-i))/((double)(m-i+n-j));
			f[i+1][j]+=f[i][j]*x,f[i][j+1]+=f[i][j]*(1.-x);
		}
		
	return fabs(ret);
}
*/
int main(){
/*	
	for (int i=0;i<=100;i++) {
		for (int j=0;j<=100;j++) if (i+j) {
			double x;
			if (i<j) x=0.;
			else x=((double)(i-j+1))/((double) (i+1));
		
			if (fabs(x-calc(i,j))>=1e-8) printf("%d %d\n",i,j);
			//printf("%d %d: %f %f\n",i,j,x,calc(i,j));
		}
	}
*/
	int T; scanf("%d",&T);
	
	while (T--) {
		int i,j; scanf("%d%d",&i,&j);
		
		double x;
		if (i<j) x=0.;
		else x=((double)(i-j+1))/((double) (i+1));
		
		printf("%.8f\n",x);
	}

	return 0;
} 
