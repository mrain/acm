#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define maxn (200)

int G[maxn][maxn];
int n, m, ans;

void init() {
	scanf("%d%d", &n, &m);
	
	for (int i = 0; i < m; ++i) {
		int x, y, z; scanf("%d%d%d", &x, &y, &z);
		G[x][y] = G[y][x] = z;
	}
}

void DP(vector<int>& P) {
/*
	for(int i=0;i<P.size();++i)
		printf("%d ",P[i]);
	puts("");
*/
	int N = P.size(), Bound = 1 << N;
	for (int i = 0; i < Bound; ++i) {
		int cnt = 0;
	
		for (int j = 0; j < N; ++j) {
			if ((i & (1 << j)) == 0) continue;
			
			int now = -1;
			for (int k = 0; k < N; ++k) {
				if ((i & (1 << k)) == 0 || j == k) continue;
				
				if (now == -1 || now > G[P[j]][P[k]]) now = G[P[j]][P[k]];
			}
				
			cnt += max(now, -1);
		}	
		
		ans = max(ans, cnt);
	}
}

int ne[maxn],ce[maxn],list[maxn][maxn];
vector<int> d;
inline void dfs(int size) {
	int i,j,k,t,cnt,best=0;
	bool bb;
	if(ne[size]==ce[size]){
		if(ce[size]==0)
			DP(d);
		return;
	}
	for(t=0,i=1;i<=ne[size];++i){
		for(cnt=0,j=ne[size]+1;j<=ce[size];++j)
			if(!G[list[size][i]][list[size][j]])++cnt;
			if(t==0||cnt<best)t=i,best=cnt;
	}
	if(t&&best<=0)return;
	for(k=ne[size]+1;k<=ce[size];++k){
		if(t>0){
			for(i=k;i<=ce[size];++i)
				if(!G[list[size][t]][list[size][i]])break;
			swap(list[size][k],list[size][i]);
		}
		i=list[size][k];
		ne[size+1]=ce[size+1]=0;
		for(j=1;j<k;++j)
			if(G[i][list[size][j]])
				list[size+1][++ne[size+1]]=list[size][j];
		for(ce[size+1]=ne[size+1],j=k+1;j<=ce[size];++j)
			if(G[i][list[size][j]])
				list[size+1][++ce[size+1]]=list[size][j];
		
		d.push_back(i);
		dfs(size+1);
		d.pop_back();
		++ne[size];
		--best;
		
		for(j=k+1,cnt=0;j<=ce[size];++j)
			if(!G[i][list[size][j]])++cnt;
		if(t==0||cnt<best)t=k,best=cnt;
		if(t&&best<=0)break;
	}
}


inline void work(){
	ne[0]=ce[0]=0;
	for(int i=1;i<=n;++i)list[0][++ce[0]]=i;
	dfs(0);
}

int main() {
	init();
	work();

	printf("%d\n", ans);

	return 0;
}
