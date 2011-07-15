#include<cstdio>
#include<cstdlib>
#include<cstring>
char s[1003],t[1003];
int n,f[1003][1003];
int main()
{
	int _;
	for(scanf("%d",&_);_--;)
	{
		scanf("%d",&n);
		scanf("%s",s+1);
		scanf("%s",t+1);
		for(int i=0;i<=n;++i)
			f[i][0]=f[0][i]=0;
		bool OK=false;
		int limit=(n+1)/2;
		for(int i=1;i<=n&&!OK;++i)
			for(int j=1;j<=n;++j)
			{
				if(abs(s[i]-t[j])<2)
					f[i][j]=f[i-1][j-1]+1;
				else
					f[i][j]=0;
				if(f[i][j]>=limit)
				{
					OK=true;
					break;
				}
			}
		if(OK)puts("POSITIVE");
		else puts("NEGATIVE");
	}
	return 0;
}
