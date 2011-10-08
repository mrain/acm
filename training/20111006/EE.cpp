#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

int n,m,sz,ed[1003],ban;
struct edge{
	int y,v,nt;
	edge(){}
	edge(int y,int v,int nt):y(y),v(v),nt(nt){}
};
edge e[100003];
inline void add(int x,int y,int v){
	e[++sz]=edge(y,v,ed[x]);
	ed[x]=sz;
}

int Q[10003],d[1003],/*dd[1003],*/fa[1003],ffa[1003];
bool in[1003];
void SPFA(int S,int T){
	int l=0,r=1;
	memset(d,63,sizeof(d));
//	memset(dd,63,sizeof(dd));
	d[S]=0;//dd[S]=0;
	Q[l]=S;in[S]=1;
	while(l!=r){
		int x=Q[l++];
		in[x]=0;
		if(l==10003)l=0;
		for(int i=ed[x];i;i=e[i].nt){
			if(i==ban||i==(ban^1))continue;
			int y=e[i].y;
			if(d[x]+e[i].v<d[y]/*||(d[x]+e[i].v==d[y]&&dd[x]+1<dd[y])*/){
				d[y]=d[x]+e[i].v;
//				dd[y]=dd[x]+1;
				fa[y]=i;
				if(!in[y]){
					Q[r]=y;in[y]=1;
					if(d[Q[r]]<d[Q[l]])swap(Q[l],Q[r]);
					++r;
					if(r==10003)r=0;
				}
			}
		}
	}
}
int main(){
	int _;
	for(scanf("%d",&_);_--;){
		scanf("%d%d",&n,&m);
		sz=1;
		memset(ed,0,sizeof(ed));
		for(int i=1;i<=m;++i){
			int x,y,v;
			scanf("%d%d%d",&x,&y,&v);
			add(x,y,v);
			add(y,x,v);
		}
		ban=0;SPFA(1,n);
		int p = d[n];
		int u=n,ans=0;
		memcpy(ffa,fa,sizeof(fa));
		while(u!=1){
			ban=ffa[u];
			SPFA(1,n);
			ans=max(ans,d[n]);
			if (ans == p) break;
			u=e[ban^1].y;
		}
		if(ans<10000000)printf("%d\n",ans);
		else puts("-1");
	}
	return 0;
}
