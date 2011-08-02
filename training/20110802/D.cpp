#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

#define maxn (150)
#define MP make_pair

typedef pair<int,int> PII;

queue<PII> q;
int dis[maxn][maxn],g[maxn][maxn];
bool vis[maxn][maxn];
int n;

const int dx[4]={1,-1,0,0},dy[4]={0,0,-1,1};

void relax(int x,int y,int v) {
	if (x<=0||y<=0||x>n||y>n) return ;
	if (dis[x][y]!=-1&&dis[x][y]<=v) return ;
	
	dis[x][y]=v;
	if (!vis[x][y]) q.push(MP(x,y)),vis[x][y]=true;
}

int main(){
	int cases=0;

	while (scanf("%d",&n)==1&&n) {
		printf("Problem %d: ",++cases);
		
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				scanf("%d",&g[i][j]);
		
		memset(dis,-1,sizeof(dis)); memset(vis,0,sizeof(vis));
		while (!q.empty()) q.pop();
		relax(1,1,g[1][1]);
		
		while (!q.empty()) {
			int X=q.front().first,Y=q.front().second; q.pop();
			vis[X][Y]=false;
			
			for (int i=0;i<4;i++)
				relax(X+dx[i],Y+dy[i],dis[X][Y]+g[X+dx[i]][Y+dy[i]]);
		}	
		
		printf("%d\n",dis[n][n]);
	}

	return 0;
}
