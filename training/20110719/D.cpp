#include<cstdio>
#include<cmath>
long double f[603][3603];
int main()
{
	f[0][0]=100;
	for(int i=0;i<602;++i)
		for(int j=i;j<=i*6;++j)
			for(int k=1;k<=6;++k)
				f[i+1][j+k]+=f[i][j]/6.0;
	int _;
	for(scanf("%d",&_);_--;)
	{
		int n,k;
		scanf("%d%d",&n,&k);
		if(n>600)puts("0");
		else if(k>n*6)puts("0");
		else printf("%d\n",(int)f[n][k]);
	}
	return 0;
}
