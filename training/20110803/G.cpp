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
int m,n;
map<PII, vector<PII> > e;
set<PIII> hash;
queue<PIII> q;
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
			e[MP(X,Y)].PB(MP(x-X,y-Y));
			
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
	
	e.clear();
	for (int i=1;i<=m;i++) 
		for (int j=1;j<=n;j++) {
			if (cnt[i][j]<2) continue;
			
			for (int k=0;k<4;k++) 
				add_edge(i,j,k);		
		}
}

bool operator<(const PII& a,const PII& b) {
	return atan2(a.B,a.A)<atan2(b.B,b.A);
}

void work(){
	init();
	
	//puts("!!");
	
	while (!q.empty()) q.pop();
	hash.clear();
	int ans=0;
	
	int sum=0;
	
	for (int i=1;i<=m;i++)
		for (int j=1;j<=n;j++) {
			if (cnt[i][j]<2) continue;
			
			vector<PII>& E=e[MP(i,j)];
			sort(E.begin(),E.end());
			
			for (int k=0;k<E.size();k++)
				q.push(MP(MP(i,j),MP(E[k].A+i,E[k].B+j))),sum++;
/*			
			printf("(%d,%d):\n",i,j);
			for (int k=0;k<E.size();k++)
				printf("(%d,%d) ",E[k].A+i,E[k].B+j);
			puts("");
*/
		}
		
	printf("%d\n",sum);
	
	while (!q.empty()) {
		PII last=q.front().A,now=q.front().B; q.pop();
		int Cnt=0;
		
		//printf("Start: (%d,%d) - > (%d,%d)\n",last.A,last.B,now.A,now.B);
		
		if (hash.find(MP(last,now))!=hash.end()) continue;
		
		while (hash.find(MP(last,now))==hash.end()) {
			//printf("(%d,%d) - > (%d,%d)\n",last.A,last.B,now.A,now.B);
		
			hash.insert(MP(last,now)),Cnt++;
			
			vector<PII>& E=e[now];
			vector<PII>::iterator it=upper_bound(E.begin(),E.end(),MP(now.A-last.A,now.B-last.B));
			
			if (it==E.end()) it=E.begin();
			
			PII tmp=MP(now.A+it->A,now.B+it->B);
			last=now; now=tmp;
			//printf("(%d,%d) - > (%d,%d)\n",last.A,last.B,now.A,now.B);
		}
			
		if (Cnt==4) ans++;
	}
	
	printf("%d\n",ans);

}

int main(){
	int T; scanf("%d",&T);
	
	while (T--) work();

	return 0;
}
