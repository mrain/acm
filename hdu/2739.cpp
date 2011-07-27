#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (1100)
#define PB push_back

struct point{
	int x,y,z,id;
}g[maxn];

int cnt[maxn],ans[maxn];
int d[maxn][maxn];
bool vis[maxn];
vector<int> e[maxn];
int n;

void dfs(int x,int v,int fa) {
	cnt[fa]=max(v,cnt[fa]);
	vis[x]=true;
	
	for (int i=0;i<e[x].size();i++) {
		int k=e[x][i]; if (vis[k]) continue;
		dfs(k,v+1,fa);
	}
}

void work() {
	for (int i=1;i<=n;i++) scanf("%d%d%d%d",&g[i].id,&g[i].x,&g[i].y,&g[i].z);
	for (int i=1;i<=n;i++) e[i].clear();
	
	for (int a=1;a<=n;a++)
		for (int b=1;b<=n;b++)
			d[a][b]=(g[a].x-g[b].x)*(g[a].x-g[b].x)+(g[a].y-g[b].y)*(g[a].y-g[b].y)+(g[a].z-g[b].z)*(g[a].z-g[b].z);
	
	for (int k=2;k<=n;k++) {
		int x=1;
	
		for (int i=2;i<k;i++) if (d[x][k]>d[i][k]) x=i;
		
		e[x].PB(k),e[k].PB(x);
	}
	
	for (int k=1;k<=n;k++) {
		for (int i=1;i<=n;i++) vis[i]=false; cnt[k]=0;
		dfs(k,0,k);
	}	
	
	int opt=cnt[1];
	for (int i=2;i<=n;i++) opt=min(opt,cnt[i]);
	
	int num=0;
	for (int i=1;i<=n;i++) if (cnt[i]==opt) ans[++num]=g[i].id;
	
	sort(ans+1,ans+1+num);
	for (int i=1;i<num;i++) printf("%d ",ans[i]); printf("%d\n",ans[num]);
}

int main(){
	
	while (scanf("%d",&n)==1&&n) work();

	return 0;
}
