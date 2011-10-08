#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1003;
const int oo=(~0U>>1);
int n,m,mm;
int sz,ed[N],cnt[N],h[N],ans[400003];
bool vs[N],vt[N];
struct edge{
	int y,v,nt;
	edge(){}
	edge(int y,int v,int nt):y(y),v(v),nt(nt){}
}e[400003];
inline void add(int x,int y,int z){
	e[++sz]=edge(y,z,ed[x]);
	ed[x]=sz;
	e[++sz]=edge(x,0,ed[y]);
	ed[y]=sz;
}	
int aug(int u,int t){
	if(u==n)return t;
	int l=t,minh=n;
	for(int i=ed[u];i;i=e[i].nt){
		if(e[i].v<1)continue;
		int v=e[i].y;
		if(h[v]+1==h[u]){
			int tmp=min(t,e[i].v);
			tmp=aug(v,tmp);
			e[i].v-=tmp;
			e[i^1].v+=tmp;
			t-=tmp;
			if(h[1]>n)return l-t;
			if(!t)break;
		}
		minh=min(minh,h[v]);
	}
	if(l==t){
		--cnt[h[u]];
		if(!cnt[h[u]])
			h[1]=n+1;
		h[u]=minh+1;
		++cnt[h[u]];
	}
	return l-t;
}
queue<int> Q;
void BFS(int u,bool *r,int d){
	Q.push(u);
	r[u]=1;
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		for(int i=ed[x];i;i=e[i].nt){
			if(e[i^d].v<1)continue;
			int y=e[i].y;
			if(!r[y]){
				Q.push(y);
				r[y]=1;
			}
		}
	}
}
int main(){
	int _,cas=0;
	for(scanf("%d",&_);_--;){
		scanf("%d%d%d",&n,&m,&mm);
		memset(ed,0,sizeof(ed));
		sz=1;
		for(int i=1;i<=m;++i){
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			add(x,y,z);
		}
		int aans=0;
		for(int i=1;i<=mm;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,n+1,y);
			aans+=y;
		}
		++n;
		memset(h,0,sizeof(h));
		memset(cnt,0,sizeof(cnt));
		cnt[0]=n;
		while(h[1]<=n)
			aans-=aug(1,oo);
		printf("Case %d: %d\n",++cas,aans);
		memset(vs,0,sizeof(vs));
		memset(vt,0,sizeof(vt));
		BFS(1,vs,0);
		BFS(n,vt,1);
		ans[0]=0;
		for(int i=1;i<n;++i)
			if(vs[i])
				for(int j=ed[i];j;j=e[j].nt){
					if(e[j].v||(j&1))continue;
					int k=e[j].y;
					if(vt[k]&&k!=n)
						ans[++ans[0]]=(j>>1);
				}
		printf("%d",ans[0]);
		for(int i=1;i<=ans[0];++i)
			printf(" %d",ans[i]);
		puts("");
	}
	return 0;
}
