#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define maxn (500000)

vector<int> g[maxn];
int dfn[maxn],low[maxn],color[maxn],stack[maxn],din[maxn],dout[maxn],f[maxn];
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

int find(int x) {
	if (!f[x]) return x;
	return f[x]=find(f[x]);
}

int main(){
	int T; scanf("%d",&T);
	
	while (T--) {
		scanf("%d%d",&n,&m);
		
		for (int i=1;i<=n;i++) g[i].clear();
		memset(f,0,sizeof(f));
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(color,0,sizeof(color));
		memset(instack,0,sizeof(instack));
		int ans=-n; c=top=timer=0;
		
		for (int i=0;i<m;i++) {
			int x,y; scanf("%d%d",&x,&y);
			g[x].push_back(y);
			
			x=find(x),y=find(y);
			if (x!=y) f[y]=x,ans++;
		}
		
		for (int i=1;i<=n;i++) if (!dfn[i]) dfs(i);
/*		
		for (int i=1;i<=n;i++) printf("%d %d\n",i,color[i]);
*/		
		if (c==1) {
			puts("0"); continue;
		}
		
		memset(din,0,sizeof(din));
		memset(dout,0,sizeof(dout));
		for (int i=1;i<=n;i++) {
			for (int j=0;j<g[i].size();j++) {
				int k=g[i][j];
				
				if (color[i]!=color[k]) din[color[k]]++,dout[color[i]]++;
			}
		}
		
		for (int i=1;i<=c;i++) if (!din[i]) ans++;
		for (int i=1;i<=c;i++) if (!dout[i]) ans++;
		
		printf("%d\n",ans);
	}

	return 0;
}
