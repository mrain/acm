#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <deque>
#include <queue>

using namespace std;

#define maxn (1100)
#define PB push_back
#define MP make_pair
#define A first 
#define B second

typedef pair<int,int> PII;
typedef pair<PII,PII> PIII;

bool vis[maxn][maxn][4];
int cnt[maxn][maxn];
int m,n,V,E;
char buf[10];

const int dx[4]={1,1,-1,-1},dy[4]={1,-1,-1,1};

void go(int x,int y,int d) {
	int step=0;

	while (true) {
		if (step!=0&&(x==1&&y==1||x==1&&y==n||x==m&&y==1||x==m&&y==n)) break;
		if (vis[x][y][d]) break;
		
		vis[x][y][d]=true,cnt[x][y]++,step++;
		
		int X=x+dx[d],Y=y+dy[d],D=d;
		if (X>m||X<1) D=3-d;
		if (Y>n||Y<1) D^=1;
		
		if (D!=d) d=D;
		else x=X,y=Y;
	}
}

inline void add_edge(int X,int Y,int d) {
	int x=X,y=Y;
	
	while (true) {
		x-=dx[d],y-=dy[d];
		
		if (x<0||x>m||y<0||y>n) break;
		
		if (cnt[x][y]>=2) {
			E++;
			
			break;
		}
	}
}

void init(){	
	memset(vis,0,sizeof(vis)); memset(cnt,0,sizeof(cnt));
	scanf("%d%d",&m,&n);
	int M,N; scanf("%d%d",&M,&N);
	scanf("%s",buf);
	
	int D;
	if (buf[0]=='D') {
		if (buf[1]=='R') D=0;
		else D=1;
	}
	else {
		if (buf[1]=='L') D=2;
		else D=3;
	}
	
	go(M,N,D);
}

bool operator<(const PII& a,const PII& b) {
	return atan2(a.B,a.A)<atan2(b.B,b.A);
}

void work(){
	init();
	
	V=0,E=0;
	for (int i=1;i<=m;i++) 
		for (int j=1;j<=n;j++) {
			if (cnt[i][j]<2) continue;
			
			V++;
			for (int k=0;k<4;k++) 
				if (vis[i][j][k]) add_edge(i,j,k);		
		}
	
	if (V<4) puts("0");
	else printf("%d\n",1+E-V);
}

int main(){
	int T; scanf("%d",&T);
	
	while (T--) work();

	return 0;
}
