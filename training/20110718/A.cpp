#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (311)
#define MP make_pair
#define PB push_back
#define A first
#define B second

typedef pair<int,int> PII;

int g[maxn][maxn][5];
int dis[maxn][maxn];
int m,n,stx,sty;

PII q[maxn*maxn];

const int dx[5]={0,1,-1,0,0},dy[5]={0,0,0,1,-1};

const int bound=205;

void init(){
	memset(g,0,sizeof(g));
	
	for (int i=1;i<=m;i++) {
		int x,y,d,t; scanf("%d%d%d%d",&x,&y,&d,&t);
		
		if (d==0) {
			for (int i=x;i<x+t;i++) 
				g[i][y][4]=g[i][y-1][3]=-1;
		}
		else {
			for (int i=y;i<y+t;i++)
				g[x][i][2]=g[x-1][i][1]=-1;
		}
	}
	
	for (int i=1;i<=n;i++) {
		int x,y,d; scanf("%d%d%d",&x,&y,&d);
		
		if (d==0) {
			g[x][y][4]=g[x][y-1][3]=1;
		}
		else { 
			g[x][y][2]=g[x-1][y][1]=1;
		}
	}
	
	double x,y; scanf("%lf%lf",&x,&y);
	stx=x,sty=y;
	
	if (stx>bound) stx=bound;
	if (sty>bound) sty=bound;
}

void work(){
	memset(dis,-1,sizeof(dis));

	int head=0,tail=0; q[tail]=MP(stx,sty);
	dis[stx][sty]=0;
	
	while (head<=tail) {
		for (int i=head;i<=tail;i++) {
			int x=q[i].A,y=q[i].B;
			
			if (x==0&&y==0) {
				printf("%d\n",dis[0][0]); return ;
			}
/*		
			printf("%d %d :%d\n",x,y,dis[x][y]);
*/	
			for (int k=1;k<=4;k++) {
				if (g[x][y][k]!=0) continue;
			
				int X=x+dx[k],Y=y+dy[k];
				if (X<0||Y<0||X>bound||Y>bound||dis[X][Y]!=-1) continue; 
			
				dis[X][Y]=dis[x][y]+g[x][y][k],q[++tail]=MP(X,Y);
			}
		}
		
		int tmp=tail;
		
		for (int i=head;i<=tmp;i++) {
			int x=q[i].A,y=q[i].B;
/*		
			printf("%d %d :%d\n",x,y,dis[x][y]);
*/		
			for (int k=1;k<=4;k++) {
				if (g[x][y][k]!=1) continue;
			
				int X=x+dx[k],Y=y+dy[k];
				if (X<0||Y<0||X>bound||Y>bound||dis[X][Y]!=-1) continue; 
			
				dis[X][Y]=dis[x][y]+g[x][y][k],q[++tail]=MP(X,Y);
			}
		}
		
		head=tmp+1;
	}
	
	printf("%d\n",dis[0][0]);
} 

int main(){
	while (scanf("%d%d",&m,&n)==2&&(m!=-1&&n!=-1)) {
		init();
		work();
	}

	return 0;
}
