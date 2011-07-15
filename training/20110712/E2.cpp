#include<cstdio>
#include<vector>
#include<algorithm>
#define PB push_back
using namespace std;
int n,m,fa[10003],mk,mark[10003];
bool vis[10003];
vector<int> e[10003];
int find(int u)
{
	if(fa[u]==u)return u;
	else return fa[u]=find(fa[u]);
}
void Tarjan(int father,int u)
{
	if(vis[u])return;
	vis[u]=true;
	for(int i=0;i<e[u].size();++i)
	{
		int v=e[u][i];
		if(v==father)continue;
		Tarjan(u,v);
	}
	int cnt=0;
	for(int i=0;i<e[u].size();++i)
	{
		int v=find(e[u][i]);
		if(mark[v]!=u)
		{
			++cnt;
			mark[v]=u;
		}
	}
	for(int i=0;i<e[u].size();++i)
	{
		int v=e[u][i];
		if(v!=father)
			fa[find(v)]=find(u);
	}
	printf("%d %d\n",u,cnt);
	if(cnt>mk)mk=cnt;
}
int main()
{
	while(scanf("%d%d",&n,&m),n+m)
	{
		for(int i=1;i<=n;++i)
			e[i].clear();
		for(int i=1;i<=m;++i)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			++x,++y;
			e[x].PB(y),e[y].PB(x);
		}
		int ans=0,best=-1;
		for(int i=1;i<=n;++i)fa[i]=i,vis[i]=mark[i]=0;
		for(int i=1;i<=n;++i)
			if(!vis[i])
			{
				++ans;
				mk=0;
				Tarjan(0,i);
				if(mk-1>best)
					best=mk-1;
			}
		printf("%d\n",ans+best);
	}
	return 0;
}
