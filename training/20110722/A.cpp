#include<cstdio>
#include<cstring>
int n,g[11],f[257][257],ans;
int search(int now,int dai)
{
	if(now==(1<<n)-1)
		return 1;
	int &ret=f[now][dai];
	if(ret!=-1)return ret;
	ret=0;
	for(int i=1;i<=n;++i)
		if(dai&(1<<i-1))
		{
			for(int j=0;j<(1<<n);++j)
				if((j&now)==0&&(g[i]&j)==j)
					ret+=search(now|j,dai^(1<<i-1)|j);
			break;
		}
	return ret;
}
int main()
{
	while(scanf("%d",&n),n)
	{
		for(int i=1;i<=n;++i)g[i]=0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
			{
				char ch=' ';
				while(ch!='0'&&ch!='1')ch=getchar();
				if(ch=='1')
					g[i]|=(1<<j-1);
			}
		memset(f,-1,sizeof(f));
		ans=0;
		for(int i=1;i<=n;++i)
			ans+=search(1<<i-1,1<<i-1);
		printf("%d\n",ans);
	}
	return 0;
}
