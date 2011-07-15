#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define PB push_back
using namespace std;
const int MX=10003;
int n,m,DFSTime,best,dfn[MX],low[MX];
vector<int> e[MX];
void Tarjan(int fa,int u)
{
	dfn[u]=low[u]=++DFSTime;
	int cnt1=0,cnt2=0;
	for(int i=0;i<e[u].size();++i)
	{
		int v=e[u][i];
		if(v==fa)continue;
		else
		{
			if(!dfn[v])
			{
				Tarjan(u,v);
				low[u]=min(low[u],low[v]);
				if(low[v]>dfn[u])++cnt1;
				else if(low[v]==dfn[u])++cnt2;
			}
			else
				low[u]=min(low[u],dfn[v]);
		}
	}
	if(fa!=-1)
	{
		if(low[u]>dfn[fa])++cnt1;
		if(low[u]<=dfn[fa])++cnt2;
	}
	//printf("%d %d %d\n",u,cnt1,cnt2);
	if(cnt1||cnt2>1)
		best=max(best,cnt1+cnt2);
}
int main()
{
	while(scanf("%d%d",&n,&m),n+m)
	{
		for(int i=0;i<n;++i)
			e[i].clear();
		for(int i=1;i<=m;++i)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			e[x].PB(y),e[y].PB(x);
		}
		int ans=0;
		memset(dfn,0,sizeof(dfn));
		for(int i=0;i<n;++i)
			if(!dfn[i])
			{
				DFSTime=0;
				best=1;
				Tarjan(-1,i);
				ans+=best;
			}
		printf("%d\n",ans);
	}
	return 0;
}
