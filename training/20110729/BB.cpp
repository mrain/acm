#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define maxn (500000)

vector<int> g[maxn],e[maxn];
int dfn[maxn],low[maxn],color[maxn],stack[maxn],pre[maxn],vis[maxn];
bool instack[maxn];
int timer,m,n,top,c;

void dfs(int x) {
	timer++;
	dfn[x]=low[x]=timer;
	stack[++top]=x,instack[x]=true;
	
	for (int i=0;i<g[x].size();i++) {
		int k=g[x][i];
		
		if (!dfn[k]) {
			dfs(k); low[x]=min(low[x],low[k]);
		}
		else {
			if (instack[k]) low[x]=min(low[x],dfn[k]);
		}
	}
	
	if (low[x]==dfn[x]) {
		int k; c++;
	
		do {
			k=stack[top--];
			instack[k]=false,color[k]=c;
		} while (k!=x);
	}
}

bool find(int x) {
	if (vis[x]==timer) return false;
	vis[x]=timer;
	
	for (int i=0;i<e[x].size();i++) {
		int y=e[x][i];
		if (!pre[y]||find(pre[y])) {
			pre[y]=x; return true;
		}
	}
	
	return false;
}

int main(){
	int T; scanf("%d",&T);
	
	while (T--) {
		scanf("%d%d",&n,&m);
		
		for (int i=1;i<=n;i++) g[i].clear();
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(color,0,sizeof(color));
		memset(instack,0,sizeof(instack));
		c=top=timer=0;
		
		for (int i=0;i<m;i++) {
			int x,y; scanf("%d%d",&x,&y);
			g[x].push_back(y);
		}
		
		for (int i=1;i<=n;i++) if (!dfn[i]) dfs(i);
/*		
		for (int i=1;i<=n;i++) printf("%d %d\n",i,color[i]);
*/		
		if (c==1) {
			puts("0"); continue;
		}
		
		for (int i=1;i<=c;i++) e[i].clear();
		for (int i=1;i<=n;i++) {
			for (int j=0;j<g[i].size();j++) {
				int k=g[i][j];
				
				if (color[i]!=color[k]) e[color[i]].push_back(color[k]);
			}
		}
		
		int ans=c; timer=0;
		memset(vis,0,sizeof(vis));
		memset(pre,0,sizeof(pre));
		for (int i=1;i<=c;i++) {
			timer++;
			
			if (find(i)) ans--;
		}
		
		printf("%d\n",ans);
	}

	return 0;
}
