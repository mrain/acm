#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>
#define pb push_back
#define A first
#define B second
const int MX=100003;
using namespace std;
int n,m,d[MX],ed[MX];
struct edge
{
	int y,v,nt;
	edge(){}
}e[MX*4+1];
int q[MX],sz;
int a[2][MX];
bool vis[MX];
int main()
{
	int _;
	for(scanf("%d",&_);_--;)
	{
		scanf("%d%d",&n,&m);
		sz=0;
		memset(ed,0,sizeof(ed));
		for(int i=1;i<=m;++i)
		{
			int x,y,v;
			scanf("%d%d%d",&x,&y,&v);
			e[++sz].y=y,e[sz].v=v,e[sz].nt=ed[x];
			ed[x]=sz;
			e[++sz].y=x,e[sz].v=v,e[sz].nt=ed[y];
			ed[y]=sz;
		}
		memset(d,-1,sizeof(d));
		d[n]=0;
		int l=0,r=1;
		q[0]=n;
		while(l!=r)
		{
			int x=q[l++];
			for(int i=ed[x];i;i=e[i].nt)
			{
				int y=e[i].y;
				if(d[y]==-1)
				{
					d[y]=d[x]+1;
					q[r++]=y;
				}
			}
			if (d[1] != -1) break;
		}
		//continue;
		printf("%d\n",d[1]);
		register int now=0;
		a[now][++a[now][0]]=1;
		memset(vis,0,sizeof(vis));
		vis[1]=1;
		for(int i=d[1];i;--i)
		{
			a[now^1][0]=0;
			int v=(~0U>>1);
			for(int j=1;j<=a[now][0];++j)
			{
				int& u=a[now][j];
				for(int k=ed[u];k;k=e[k].nt)
				{
					int y=e[k].y;
					if(d[y]+1!=d[u])continue;
					v=min(v,e[k].v);
				}
			}
			printf("%d",v);
			if(i>1)putchar(' ');
			for(int j=1;j<=a[now][0];++j)
			{
				int& u=a[now][j];
				for(int k=ed[u];k;k=e[k].nt)
				{
					int y=e[k].y;
					if(d[y]+1!=d[u])continue;
					if(e[k].v!=v)continue;
					if(vis[y])continue;
					a[now^1][++a[now^1][0]]=y;
					vis[y]=1;
				}
			}
			now^=1;
		}
		puts("");
	}
	return 0;
}
