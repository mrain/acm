#include<cstdio>
const int d[]={6,2,5,5,4,5,6,3,7,6};
int v[23];
int calc(int x)
{
	int ret=0;
	while(x)
	{
		ret+=d[x%10];
		x/=10;
	}
	return ret;
}
void out_small(int x)
{
	int cnt=0;
	while(x>21)
	{
		++cnt;
		x-=7;
	}
	printf("%d",v[x]);
	for(int i=0;i<cnt;++i)putchar('8');
}
void out_big(int x)
{
	if(x&1)
	{
		putchar('7');
		x-=3;
	}
	for(int i=0;i<x/2;++i)
		putchar('1');
}
int main()
{
	for(int i=1;i<22;++i)
		v[i]=(~0U>>1);
	for(int i=1;i<=1000;++i)
	{
		int t=calc(i);
		if(v[t]>i)v[t]=i;
	}
	int _;
	for(scanf("%d",&_);_--;)
	{
		int n;
		scanf("%d",&n);
		out_small(n);
		putchar(' ');
		out_big(n);
		puts("");
	}
	return 0;
}
