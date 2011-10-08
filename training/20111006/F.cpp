#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1003;
const int MOD=10000000;
int n,m,ed[N],cnt[N],h[N],sz;
struct edge{
	int y,nt;
	long long v;
	edge(){}
	edge(int y,int nt,long long v):y(y),nt(nt),v(v){}
};
edge e[500003];
void addEdge(int x,int y,long long v){
	e[++sz]=edge(y,ed[x],v);
	ed[x]=sz;
}
long long aug(int u,long long t){
	if(u==n)return t;
	long long l=t;
	int minh=n;
	for(int i=ed[u];i;i=e[i].nt){
		if(e[i].v<1)continue;
		int y=e[i].y;
		if(h[y]+1==h[u]){
			long long tmp=min(e[i].v,t);
			tmp=aug(y,tmp);
			e[i].v-=tmp;
			e[i^1].v+=tmp;
			t-=tmp;
			if(h[1]>=n)return l-t;
			if(!t)break;
		}
		minh=min(minh,h[y]);
	}
	if(l==t){
		--cnt[h[u]];
		if(!cnt[h[u]])h[1]=n;
		h[u]=minh+1;
		++cnt[h[u]];
	}
	return l-t;
}
int main(){
	int _,cas=0;
	for(scanf("%d",&_);_--;){
		scanf("%d%d",&n,&m);
		memset(ed,0,sizeof(ed));
		sz=1;
		for(int i=1;i<=m;++i){
			int x,y,v,d;
			scanf("%d%d%d%d",&x,&y,&v,&d);
			++x,++y;
			long long V=1LL*v*MOD+1;
			addEdge(x,y,V);
			addEdge(y,x,V*d);
		}
		memset(cnt,0,sizeof(cnt));
		memset(h,0,sizeof(h));
		cnt[0]=n;
		long long ans=0;
		while(h[1]<n)ans+=aug(1,1LL<<62);
		//cout<<(1LL<<62)<<endl;
		cout<<"Case "<<++cas<<": "<<ans%MOD<<endl;
	}
	return 0;
}
