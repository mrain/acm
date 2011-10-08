#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

int f[105][105];
vector<int> e[1005];
int pre[1005], pos[1005], times[1005];
bool vis[1005];
int m1[1005],m2[1005];
int n, m, q;

const int inf = 1000000001;

inline void update(int i, int j, int v) {
	if (f[i][j] > v) f[i][j] = f[j][i] = v;
}
/*
bool find(int x) {
	if (vis[x]) return false;
	vis[x] = true;
	
	for (int i = 0; i < e[x].size(); ++i) {
		int y = e[x][i];
		
		if (pre[y] == -1 || find(pre[y])) {
			pre[y] = x; return true;		
		}
	}
	
	return false;
}
*/
int d1[1005],d2[1005];
bool bfs(){
	static queue<int> q;
	memset(d1,0,sizeof(d1));
	memset(d2,0,sizeof(d2));
	for(int i=0;i<n;++i)
		if(m1[i]==-1)
			q.push(i);
	int a,b;
	bool found=false;
	while(!q.empty()){
		a=q.front();
		q.pop();
		for(int i=0;i<e[a].size();++i){
			b=e[a][i];
			if(d2[b]==0){
				d2[b]=d1[a]+1;
				if(m2[b]==-1){
					found=1;
				}
				else{
					d1[m2[b]]=d2[b]+1;
					q.push(m2[b]);
				}
			}
		}
	}
	return found;
}

bool dfs(int a){
	for(int i=0;i<e[a].size();++i){
		int b=e[a][i];
		if(d1[a]+1==d2[b]){
			d2[b]=0;
			if(m2[b]==-1||dfs(m2[b])){
				m1[a]=b;
				m2[b]=a;
				return 1;
			}
		}
	}
	return 0;
}
int main() {

	int T; scanf("%d", &T);
	for (int cases = 1; cases <= T; ++cases) {
		printf("Case %d: ", cases);
		
		scanf("%d%d%d", &n, &m, &q);
		
		memset(pre, -1, sizeof(pre));
		
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				f[i][j] = inf;
		for (int i = 0; i < n; ++i) f[i][i] = 0;
		
		for (int i = 0; i < m; ++i) {
			int x, y, v; scanf("%d%d%d", &x, &y, &v);
			update(x, y, v);
		}
		
		for (int k = 0; k < n; ++k)
			for (int i = 0; i < n; ++i) if (f[i][k] < inf)
				for (int j = 0; j < n; ++j) if (f[k][j] < inf) 
					update(i, j, f[i][k] + f[k][j]);
					
		for (int i = 0; i < q; ++i)	scanf("%d%d", &pos[i], &times[i]);
		for (int i = 0; i < q; ++i) {
			e[i].clear();
			for (int j = 0; j < q; ++j) if (i != j) {
				if (times[j] - times[i] >= f[pos[i]][pos[j]]) e[i].push_back(j);
			}
		}
		
		int ans = q - 1;
		n=q;
		memset(m1,255,sizeof(m1));
		memset(m2,255,sizeof(m2));
		while(bfs())
			for(int i=0;i<q;++i)
				if(m1[i]==-1&&dfs(i))
					--ans;
		
		printf("%d\n", max(ans, 0));
	}	

	return 0;
}
