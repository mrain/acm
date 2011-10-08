#include<set>
#include<queue>
#include<cstdio>
#include<utility>
#include<cstring>
#include<algorithm>
#define lowbit(x) ((x)&(-(x)))
#define two(x) (1<<(x))
using namespace std;
int g[11][11],id[11][11],one[10003];
bool vis[11][11];

typedef pair<int,int> PII;
queue<PII> Q;
set<PII> h;
void BFS(int x,int y,int cnt){
	Q.push(make_pair(x,y));
	vis[x][y]=1,id[x][y]=cnt;
	while(!Q.empty()){
		PII now=Q.front();
		Q.pop();
		int &v=g[now.first][now.second];
		
		if(v<128){
			if(vis[now.first][now.second-1]==0&&now.second>1){
				Q.push(make_pair(now.first,now.second-1));
				vis[now.first][now.second-1]=1;
				id[now.first][now.second-1]=cnt;
			}
		}
		else v-=128;
		
		if(v<64){
			if(vis[now.first+1][now.second]==0&&now.first<9){
				Q.push(make_pair(now.first+1,now.second));
				vis[now.first+1][now.second]=1;
				id[now.first+1][now.second]=cnt;
			}
		}
		else v-=64;
		
		if(v<32){
			if(vis[now.first][now.second+1]==0&&now.second<9){
				Q.push(make_pair(now.first,now.second+1));
				vis[now.first][now.second+1]=1;
				id[now.first][now.second+1]=cnt;
			}
		}
		else v-=32;
		
		if(v<16){
			if(vis[now.first-1][now.second]==0&&now.first>1){
				Q.push(make_pair(now.first-1,now.second));
				vis[now.first-1][now.second]=1;
				id[now.first-1][now.second]=cnt;
			}
		}
		else v-=16;
	}
}

int line[11];
int col[11];
int block[11];
int cans,ans[11][11];

void search(int rest){
	if(cans>1)return;
	if(rest==0){
		++cans;
		memcpy(ans,g,sizeof(g));
		return;
	}
	
	int mi=10,x,y,va;
	for(set<PII>::iterator r=h.begin();r!=h.end()&&mi>1;++r){
		int i=r->first;
		int j=r->second;
		int ban=line[i]|col[j]|block[id[i][j]];
		int can=1022-ban;
		if(one[can]<mi){
			mi=one[can];
			x=i;
			y=j;
			va=can;
		}
	}
	if(mi==0)return;
	if(rest==4&&mi>1){
		cans=2;
		return;
	}
	h.erase(make_pair(x,y));
	for(int i=1;i<=9;++i)
		if(va&two(i)){
			g[x][y]=i;
			line[x]|=two(i);
			col[y]|=two(i);
			block[id[x][y]]|=two(i);
			search(rest-1);
			if(cans>1)return;
			block[id[x][y]]^=two(i);
			col[y]^=two(i);
			line[x]^=two(i);
			g[x][y]=0;
		}
	h.insert(make_pair(x,y));
}

int main(){
	for(int i=1;i<10003;++i)
		one[i]=1+one[i-lowbit(i)];
	int _,cas=0;
	for(scanf("%d",&_);_--;){
		printf("Case %d:\n",++cas);
		for(int i=1;i<=9;++i)
			for(int j=1;j<=9;++j)
				scanf("%d",g[i]+j);
		int cnt=0;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=9;++i)
			for(int j=1;j<=9;++j)
				if(!vis[i][j])
					BFS(i,j,++cnt);
		
		/*for(int i=1;i<=9;++i){
			for(int j=1;j<=9;++j)
				printf("%d ",g[i][j]);
			puts("");
		}*/
		memset(line,0,sizeof(line));
		memset(col,0,sizeof(col));
		memset(block,0,sizeof(block));
		cnt=0;
		bool noans=0;
		h.clear();
		for(int i=1;i<=9;++i)
			for(int j=1;j<=9;++j)
				if(g[i][j]){
					if(line[i]&two(g[i][j]))noans=1;
					else line[i]|=two(g[i][j]);
					if(col[j]&two(g[i][j]))noans=1;
					else col[j]|=two(g[i][j]);
					if(block[id[i][j]]&two(g[i][j]))noans=1;
					else block[id[i][j]]|=two(g[i][j]);
				}
				else{
					++cnt;
					h.insert(make_pair(i,j));
				}
		if(noans){
			puts("No solution");
			continue;
		}
		cans=0;
		search(cnt);
		if(cans>1)puts("Multiple Solutions");
		else if(cans<1)puts("No solution");
		else{
			for(int i=1;i<=9;++i){
				for(int j=1;j<=9;++j)
					printf("%d",ans[i][j]);
				puts("");
			}
		}
	}
	return 0;
}
