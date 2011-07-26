#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,best,fa[101];
struct edge
{
	int x,y,v;
	edge(){}
	edge(int _x,int _y,int _v):x(_x),y(_y),v(_v){}
	bool operator <(const edge &a)const{
		return v<a.v;
	}
}e[10003];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void work(int u)
{
	for(int i=1;i<=n;++i)fa[i]=i;
	int ret=n;
	for(int i=u;i<=m;++i)
	{
		int x=e[i].x,y=e[i].y,v=e[i].v;
		if(v-e[u].v>=best)return;
		if(find(x)!=find(y))
			fa[find(x)]=find(y),--ret;
		if(ret==1)
		{
			best=min(best,e[i].v-e[u].v);
			return;
		}
	}
}
int main()
{
	while(scanf("%d%d",&n,&m),n||m)
	{
		if(!m)
		{
			puts("-1");
			continue;
		}
		for(int i=1;i<=m;++i)
		{
			int x,y,v;
			scanf("%d%d%d",&x,&y,&v);
			e[i]=edge(x,y,v);
		}
		stable_sort(e+1,e+m+1);
		best=(~0U>>1);
		for(int i=1;i<=m;++i)
			if(i!=1||e[i].v!=e[i-1].v)
				work(i);
		if(best!=(~0U>>1))printf("%d\n",best);
		else puts("-1");
	}
	return 0;
}
