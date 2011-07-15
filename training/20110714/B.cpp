#include<cstdio>
#include<cstring>
int n,mat[213][213],ans[213][213],belong[213];
bool vis[213];
int main()
{
	while(scanf("%d",&n)==1)
	{
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				scanf("%d",mat[i]+j);
		for(int i=1;i<=n;++i)
			mat[i][i]=0;
		memset(ans,0,sizeof(ans));
		memset(vis,0,sizeof(vis));
		int cnt=0,ret=0;
		for(int i=1;i<=n;++i)
			if(!vis[i])
			{
				int tot=1;
				belong[i]=++cnt;
				for(int j=i+1;j<=n;++j)
					if(mat[i][j]&&mat[j][i])
					{
						++tot;
						vis[j]=true;
						belong[j]=cnt;
					}
				if(tot>1)ret+=tot;
			}
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(mat[i][j])
					if(belong[i]!=belong[j])
						ans[belong[i]][belong[j]]=true;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				for(int k=1;k<=n;++k)
					if(ans[j][i]&&ans[i][k]&&ans[j][k])
						ans[j][k]=false;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				ret+=ans[i][j];
		printf("%d\n",ret);
	}
	return 0;
}
