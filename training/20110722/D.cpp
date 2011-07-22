#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int n,A,B;
double P;
double calc(int x)
{
	double ret=x*P*A;
	int y=n-x;
	double S=(pow(1-P,y+1)-(1-P))/P+y;
	ret+=B*S;
	return ret;
}
double work()
{
	int l=0,r=n;
	while(l+10<r)
	{
		int k1=(l+r)>>1;
		int k2=(r+k1)>>1;
		if(calc(k1)<calc(k2))l=k1;
		else r=k2;
	}
	double ret=min(calc(0),calc(n));
	//printf("%d %d\n",l,r);
	for(int i=l;i<=r;++i)
	{
		//printf("%d %.2f\n",i,calc(i));
		ret=min(ret,calc(i));
	}
	return ret;
}
int main()
{
	int p;
	while(scanf("%d%d%d%d",&n,&p,&A,&B),n||p||A||B)
	{
		--n;
		if(n<1)
		{
			puts("0.0000");
			continue;
		}
		P=p/100.0;
		for(int i=0;i<=n;++i)
			printf("%.5f\n",calc(i));
		printf("%.4f\n",work());
	}
	return 0;
}
