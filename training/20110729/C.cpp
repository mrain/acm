#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (600)

int c[maxn][2],d[maxn][2];
int m,n,C,D,V;
bool g[maxn][maxn];
bool vis[maxn];
int pre[maxn];

bool find(int x) {
	if (vis[x]) return false;
	vis[x]=true;
	
	for (int i=1;i<=n;i++) if (g[x][i]) {
		if (!pre[i]||find(pre[i])) {
			pre[i]=x; return true;
		}
	}
	
	return false;
}

int main(){
	int T; scanf("%d",&T);
	
	while (T--) {
		scanf("%d%d%d",&C,&D,&V);
		
		m=n=0;
		for (int i=0;i<V;i++) {
			char t1,t2; int x,y;
			
			scanf(" %c%d %c%d",&t1,&x,&t2,&y);
			
			if (t1=='C') {
				m++;
				c[m][0]=x,c[m][1]=y;
			}
			else {
				n++;
				d[n][0]=x,d[n][1]=y;
			}
		}
		
		memset(g,0,sizeof(g));
		for (int i=1;i<=m;i++) 
			for (int j=1;j<=n;j++) if (c[i][0]==d[j][1]||c[i][1]==d[j][0])
				g[i][j]=true;
				
		int ans=V;
		memset(pre,0,sizeof(pre));
		for (int i=1;i<=m;i++) {
			memset(vis,0,sizeof(vis));
			if (find(i)) ans--;
		}
		
		printf("%d\n",ans);
	}

	return 0;
}
