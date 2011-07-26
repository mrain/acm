#include<cstdio>
int main()
{
	int n,k,m;
	while(scanf("%d%d%d",&n,&k,&m),n||k||m)
	{
		int s=0;
		for(int i=2;i<=n;++i)
			s=(s+k)%i;
		m=(m-1-k+2*n)%n;
		printf("%d\n",(m+s+1)%n+1);
	}
	return 0;
}
