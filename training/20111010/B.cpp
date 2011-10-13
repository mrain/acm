#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
int n,m,dfn[101],DFSTime,st[101],C,belong[101],f[101][257],du[101];
bool in[101],vis[101];
vector<int> e[101],ee[101];
const int MOD=100000;
int Tarjan(int u){
	if(dfn[u])return in[u]?dfn[u]:4*n+1;
	in[st[++st[0]]=u]=1;
	int low=dfn[u]=++DFSTime;
	for(int i=0;i<e[u].size();++i)
		low=min(low,Tarjan(e[u][i]));
	if(low==dfn[u])
		for(++C;;){
			belong[st[st[0]]]=C;
			in[st[st[0]]]=0;
			if(st[st[0]--]==u)break;
		}
	return low;
}
void work(int u){
	if(vis[u])return;
	vis[u]=1;
	for(int i=0;i<=255;++i)f[u][i]=1;
	for(int i=0;i<ee[u].size();++i)
		work(ee[u][i]);
	for(int j=0;j<=255;++j)
		for(int i=0;i<ee[u].size();++i){
			long long v=1LL*f[u][j]*f[ee[u][i]][j];
			f[u][j]=v%MOD;
		}
	for(int j=1;j<=255;++j){
		f[u][j]+=f[u][j-1];
		if(f[u][j]>=MOD)f[u][j]-=MOD;
	}
}
int main(){
	int _,cas=0;
	for(scanf("%d",&_);_--;){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=4*n;++i){
			e[i].clear();
			ee[i].clear();
		}
		for(int i=1;i<n;++i)e[i+1].push_back(i);
		for(int i=n+1;i<n+n;++i)e[i+1].push_back(i);
		for(int i=n+n+1;i<n+n+n;++i)e[i+1].push_back(i);
		for(int i=n+n+n+1;i<n+n+n+n;++i)e[i+1].push_back(i);
		for(;m--;){
			int x1,y1,x2,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			int x=n*(x1-1)+y1;
			int y=n*(x2-1)+y2;
			e[x].push_back(y);
			e[y].push_back(x);
		}
		memset(dfn,0,sizeof(dfn));
		DFSTime=C=0;
		for(int i=1;i<=4*n;++i)
			if(!dfn[i])
				Tarjan(i);
		memset(f,0,sizeof(f));
		for(int i=1;i<=4*n;++i)
			for(int j=0;j<e[i].size();++j){
				int k=e[i][j];
				if(belong[k]!=belong[i])
					ee[belong[i]].push_back(belong[k]);
			}
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=C;++i)
			work(i);
		memset(du,0,sizeof(du));
		for(int i=1;i<=C;++i)
			for(int j=0;j<ee[i].size();++j)
				++du[ee[i][j]];
		int ans=1;
		for(int i=1;i<=C;++i)
			if(!du[i]){
				long long v=1LL*f[i][255]*ans;
				ans=v%MOD;
			}
		printf("Case %d: %05d\n",++cas,ans);
	}
	return 0;
}
