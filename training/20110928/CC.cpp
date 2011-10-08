#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<utility>
#include<iostream>
#include<algorithm>
using namespace std;
const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};

int n,m,L,per[53][53],on[53][53],off[53][53];
char s[53][53];

int id[53][53];
pair<int,int> pos[2503];
int guan[2503];

vector<int> g[2503],road;

inline void add(int x,int y){
	g[x].push_back(y);
}

int vis[2503],pre[2503];
queue<int> q;
void BFS(int u,int v){
	memset(vis,0,sizeof(vis));
	vis[u]=1;
	q.push(u);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=0;i<g[x].size();++i){
			int y=g[x][i];
			if(vis[y])continue;
			vis[y]=vis[x]+1;
			pre[y]=x;
			q.push(y);
		}
	}
	while(v!=u)
		road.push_back(v=pre[v]);
}

int main(){
	scanf("%d%d%d",&n,&m,&L);
	for(int i=1;i<=n;++i)
		scanf("%s",s[i]+1);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",per[i]+j);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",on[i]+j);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",off[i]+j);
	
	int cnt=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(s[i][j]=='.'){
				id[i][j]=++cnt;
				pos[cnt]=make_pair(i,j);
			}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int k=0;k<4;++k){
				int ii=i+dx[k];
				int jj=j+dy[k];
				if(ii>0&&ii<=n&&jj>0&&jj<=m&&s[ii][jj]=='.')
					add(id[i][j],id[ii][jj]);
			}
			
	int x,y;
	scanf("%d%d",&x,&y);
	int u=id[++x][++y];road.push_back(u);
	for(int i=1;i<L;++i){
		scanf("%d%d",&x,&y);
		++x,++y;
		//printf("%d %d\n",u,id[x][y]);
		BFS(id[x][y],u);
		u=id[x][y];
	}
	long long ans=0;
	for(int i=0;i<road.size();++i){
		//printf("%d\n",road[i]);
		int u=road[i];
		ans+=on[pos[u].first][pos[u].second];
		ans+=off[pos[u].first][pos[u].second];
	}
	
	memset(guan,-1,sizeof(guan));
	for(int i=0;i<road.size();++i){
		int u=road[i];
		if(guan[u]!=-1)
			if((long long)off[pos[u].first][pos[u].second]+on[pos[u].first][pos[u].second]>1LL*(i-guan[u])*per[pos[u].first][pos[u].second]){
				ans-=off[pos[u].first][pos[u].second]+on[pos[u].first][pos[u].second];
				ans+=1LL*(i-guan[u])*per[pos[u].first][pos[u].second];
			}
			guan[u]=i;
	}
	cout<<ans<<endl;
	return 0;
}
