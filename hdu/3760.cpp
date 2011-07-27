#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
#include<utility>
#include<algorithm>
#define mp make_pair
#define pb push_back
#define A first
#define B second
const int MX=200003;
using namespace std;
int n,m,d[MX];
vector< pair<int,int> > e[MX];
queue<int> q;
vector<int> a[2];
bool vis[MX];
int main()
{
	int _;
	for(scanf("%d",&_);_--;)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)e[i].clear();
		for(int i=1;i<=m;++i)
		{
			int x,y,v;
			scanf("%d%d%d",&x,&y,&v);
			e[x].pb(mp(y,v));
			e[y].pb(mp(x,v));
		}
		memset(d,-1,sizeof(d));
		d[n]=0;q.push(n);
		while(!q.empty())
		{
			int x=q.front();q.pop();
			for(int i=0;i<e[x].size();++i)
			{
				pair<int,int> y=e[x][i];
				if(d[y.A]==-1)
				{
					d[y.A]=d[x]+1;
					q.push(y.A);
				}
			}
		}
		printf("%d\n",d[1]);
		int now=0;
		a[now].clear();
		a[now].pb(1);
		memset(vis,0,sizeof(vis));
		vis[1]=1;
		for(int i=d[1];i;--i)
		{
			a[now^1].clear();
			int v=(~0U>>1);
			for(int j=0;j<a[now].size();++j)
			{
				int u=a[now][j];
				for(int k=0;k<e[u].size();++k)
				{
					pair<int,int> y=e[u][k];
					if(d[y.A]+1!=d[u])continue;
					v=min(v,y.B);
				}
			}
			printf("%d",v);
			if(i>1)putchar(' ');
			for(int j=0;j<a[now].size();++j)
			{
				int u=a[now][j];
				for(int k=0;k<e[u].size();++k)
				{
					pair<int,int> y=e[u][k];
					if(d[y.A]+1!=d[u])continue;
					if(y.B!=v)continue;
					if(vis[y.A])continue;
					a[now^1].pb(y.A);
					vis[y.A]=1;
				}
			}
			now^=1;
		}
		puts("");
	}
	return 0;
}
