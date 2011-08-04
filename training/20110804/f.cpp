#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

#define maxn (30)
#define MP make_pair
#define PB push_back
#define A first 
#define B second

typedef pair<int,int> PII;
typedef pair<int,PII> PIII;

vector<PII> e1[maxn][maxn],e2[maxn][maxn],e0[maxn][maxn];
int dis[maxn][maxn][maxn];
queue<PIII> q; 
int n,m,st,ed;
 
void init(){
	scanf("%d%d",&n,&m);
	
	int tot; scanf("%d",&tot);

	for (int i=1;i<=tot;i++) {
		int x1,y1;
		int x2,y2;
		scanf(" %d ",&x1);
		scanf(" . ");
		scanf(" %d ",&y1);
		scanf(" - ");
		scanf(" %d ",&x2);
		scanf(" . ");
		scanf(" %d ",&y2);
		
		if (x1>x2) {
			swap(x1,x2),swap(y1,y2);
		}
		
		if (x1==x2) {
			for (int i=1;i<=m;i++) e0[i][y1].PB(MP(i,y2)),e0[i][y2].PB(MP(i,y1));
		}
		else {
			if (x1==0) {
				for (int i=1;i<=m;i++)
					e1[i][y1].PB(MP(x2,y2)),e2[x2][y2].PB(MP(i,y1)),e2[i][y1].PB(MP(x2,y2)),e1[x2][y2].PB(MP(i,y1));
			}
			else e1[x1][y1].PB(MP(x2,y2)),e2[x2][y2].PB(MP(x1,y1)),e2[x1][y1].PB(MP(x2,y2)),e1[x2][y2].PB(MP(x1,y1));
		}
	}
	
	scanf("%d%d",&st,&ed);
} 

inline void relax(int step,int house,int door,int v) {
	if (step<0||step>n) return ;
	if (dis[step][house][door]>-1) return ;
	
	dis[step][house][door]=v,q.push(MP(step,MP(house,door)));
}

void work() {
	memset(dis,-1,sizeof(dis));
	
	for (int i=1;i<=m;i++) relax(0,1,st,0);
	
	while (!q.empty()) {
		int step=q.front().A,house=q.front().B.A,door=q.front().B.B; q.pop();
		int v=dis[step][house][door];
		
		for (int i=0;i<e0[house][door].size();i++) {
			int S=step,H=e0[house][door][i].A,D=e0[house][door][i].B;
			
			relax(S,H,D,v+1);
		}
		
		for (int i=0;i<e1[house][door].size();i++) {
			int S=step+1,H=e1[house][door][i].A,D=e1[house][door][i].B;
			
			relax(S,H,D,v+1);
		}
		
		for (int i=0;i<e2[house][door].size();i++) {
			int S=step-1,H=e2[house][door][i].A,D=e2[house][door][i].B;
			
			relax(S,H,D,v+1);
		}
	}
	
	int ans=-1;
	for (int i=1;i<=m;i++) if (dis[0][i][ed]!=-1) {
		if (ans==-1||ans>dis[0][i][ed]) ans=dis[0][i][ed];
	}
	
	if (ans==-1) puts("no solution");
	else printf("%d\n",ans);
}

int main(){
	init();
	work();

	return 0;
}
