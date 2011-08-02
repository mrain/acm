#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int oo=(~0U>>1);
int n,m,S,T;
int sz,ed[103],limit;
char ss[103];
struct edge
{
	int y,v,nt;
	edge(){}
	edge(int y,int v,int nt):y(y),v(v),nt(nt){}
}e[50003];
int calc()
{
	if(ss[0]=='+')return 0;
	if(ss[0]=='-')return n+1;
	int ret=0;
	for(int i=0;i<strlen(ss);++i)
		ret=(ret*10)+ss[i]-'0';
	return ret;
}
void add(int x,int y,int z)
{
	e[++sz]=edge(y,z,ed[x]);
	ed[x]=sz;
	e[++sz]=edge(x,0,ed[y]);
	ed[y]=sz;
}
int h[103],cnt[103];
int aug(int u,int t)
{
	if(u==T)return t;
	int minh=limit+1,l=t;
	for(int i=ed[u];i;i=e[i].nt)
	{
		if(e[i].v<1)continue;
		int y=e[i].y;
		if(h[u]==h[y]+1)
		{
			int tmp=min(e[i].v,t);
			tmp=aug(y,tmp);
			e[i].v-=tmp;e[i^1].v+=tmp;
			t-=tmp;
			if(!t)break;
			if(h[S]>limit)return l-t;
		}
		minh=min(minh,h[y]);
	}
	if(l==t)
	{
		cnt[h[u]]--;
		if(!cnt[h[u]])h[S]=limit+1;
		h[u]=minh+1;
		++cnt[h[u]];
	}
	return l-t;
}
int main()
{
	while(scanf("%d%d",&n,&m),n||m)
	{
		sz=1;memset(ed,0,sizeof(ed));
		S=n+2,T=n+3;
		for(int i=1;i<=m;++i)
		{
			scanf("%s",ss);
			int x=calc();
			scanf("%s",ss);
			int y=calc();
			int z;
			scanf("%d",&z);
			add(x,y,oo);
			add(S,y,z);
			add(x,T,z);
		}
		int num=sz;
		add(n+1,0,oo);
		memset(h,0,sizeof(h));
		memset(cnt,0,sizeof(cnt));
		cnt[0]=n+4;
		int ans=0;
		limit=n+4;
		while(h[S]<=limit)
			ans+=aug(S,oo);
		bool OK=true;
		for(int i=ed[S];i;i=e[i].nt)
			if(e[i].v>0)
			{
				OK=false;
				break;
			}
		if(!OK)
		{
			puts("impossible");
			continue;
		}
		printf("%d\n",e[num+2].v);
		/*
		for(int i=ed[S];i;i=e[i].nt)
			e[i].v=e[i^1].v=0;
		for(int i=ed[T];i;i=e[i].nt)
			e[i].v=e[i^1].v=0;
		e[num+1].v=e[num+2].v=0;
		S=n+1,T=0;
		memset(h,0,sizeof(h));
		memset(cnt,0,sizeof(cnt));
		cnt[0]=n+2;
		limit=n+2;
		int ans2=0;
		for(int i=T;i<=S;++i)
			for(int j=ed[i];j;j=e[j].nt)
				printf("%d %d %d\n",i,e[j].y,e[j].v);
		while(h[S]<=limit)
			ans2+=aug(S,oo);
		printf("%d\n",ans-ans2);*/
	}
	return 0;
}
