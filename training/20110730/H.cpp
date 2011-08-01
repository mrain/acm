#include<cstring>
#include<cstdio>
#include<string>
#include<map>
#include<algorithm>
using namespace std;
char s[23],t[23];
map<string,int> h;

const int MX=10003;

int cnt,ed[MX],sz,sum[MX],tt[MX];
bool ex[MX];
int calc(char *s)
{
	string ss="";
	int len=strlen(s);
	for(int i=0;i<len;++i)
		ss+=s[i];
	if(h.find(ss)==h.end())h[ss]=++cnt;
	return h[ss];
}
struct edge
{
	int y,v,nt;
	edge(){}
	edge(int y,int v,int nt):y(y),v(v),nt(nt){}
}e[MX*5];
void add(int x,int y,int v)
{
	e[++sz]=edge(y,v,ed[x]);
	ed[x]=sz;
}
void DFS(int fa,int u,int c)
{
	sum[u]=c;
	for(int i=ed[u];i;i=e[i].nt)
	{
		int v=e[i].y;
		if(v==fa)continue;
		DFS(u,v,c+e[i].v);
	}
}
int main()
{
	int n,k;
	while(scanf("%d%d%*c",&n,&k)==2)
	{
		cnt=sz=0;h.clear();
		memset(ed,0,sizeof(int)*(n+1));
		memset(ex,1,n+1);
		for(int i=1;i<n;++i)
		{
			int v;
			scanf("%s%s%d%*c",s,t,&v);
			int x=calc(s);
			int y=calc(t);
			add(x,y,v),add(y,x,v);
			ex[y]=0;
		}
		tt[0]=0;
		for(int i=1;i<=n;++i)
			if(ex[i])
				tt[++tt[0]]=i;
		int ans=0;
		for(int i=1;i<=n;++i)
		{
			DFS(0,i,0);
			for(int i=1;i<=tt[0];++i)
				sum[i]=sum[tt[i]];
			stable_sort(sum+1,sum+tt[0]+1);
			int tmp=0;
			for(int i=0;i<k;++i)
				tmp+=sum[tt[0]-i];
			ans=max(tmp,ans);
		}
		printf("%d\n",ans);
	}
	return 0;
}
