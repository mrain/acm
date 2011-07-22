#include<cstdio>
#include<algorithm>
using namespace std;
double f[2003][2];
int main()
{
	int n,p,a,b;
	scanf("%d%d%d%d",&n,&p,&a,&b);
	f[1][1]=p/100.0*a;
	f[1][0]=0;
	for(int i=2;i<=n;++i)
	{
		double x=f[i-1][0];
		double y=f[i-1][1];
		f[i][0]=min(x+b,y);
		f[i][1]=min(x+b+a,y+p/100.0*a);
	}
	printf("%.4f\n",min(f[n-1][0]+b,f[n-1][1]));
	return 0;
}
