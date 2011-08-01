#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
int n,f[101][1003],a[101];
int main()
{
	while(scanf("%d",&n),n)
	{
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		memset(f,0x3F,sizeof(f));
		for(int i=0;i<1003;++i)
			f[1][i]==std::min(abs(a[1]-i), f[1][i-1]);
		for(int i=2;i<=n;++i)
			for(int j=0;j<1003;++j)
//				for(int k=0;k<=j;++k)
				f[i][j]=std::min(f[i][j-1],f[i-1][j]+abs(a[i]-j));
		int ans=(~0U>>1);
		for(int i=0;i<1003;++i)
			if(f[n][i]<ans)
				ans=f[n][i];
		printf("%d\n",ans);
	}
	return 0;
}
