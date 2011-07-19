#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (2011)
#define MP make_pair
#define PB push_back
#define A first
#define B second

typedef pair<int,int> PII;
typedef pair<PII,int> PIII;

int size[maxn],v[maxn];
vector<int> g[maxn];
int n,root;

bool flag[maxn];

void init(){
	for (int i=1;i<=n;i++) g[i].clear();
	memset(v,0,sizeof(v));
	
	for (int i=1;i<=n;i++) scanf("%d",&v[i]);
	
	for (int i=1;i<n;i++) {
		int x,y; scanf("%d%d",&x,&y);
		g[x].PB(y);
	}
}

void dfs(int x) {
	size[x]=v[x];
	
	for (int i=0;i<g[x].size();i++) {
		int k=g[x][i]; 
		dfs(k); size[x]+=size[k];
	}
}

void add(int x) {
	for (int i=0;i<g[x].size();i++) {
		int k=g[x][i]; flag[k]=true;
	}
}
 
void work() {
	memset(size,0,sizeof(size));
	dfs(root);
	
	memset(flag,0,sizeof(flag));
	
	flag[root]=true;
	
	int ans=0;
	for (int i=1;i<=n;i++) {
		int k=-1;
		
		for (int j=1;j<=n;j++) if (flag[j]) {
			//printf("%d %d\n",j,(n-j)*v[j]+size[j]);
		
			if (k==-1||(n-j)*v[j]+size[j]<(n-k)*v[k]+size[k]) k=j;
		}
		
		//printf("%d %d\n",i,k);
		
		ans+=v[k]*i; flag[k]=false;
		
		add(k);
	}
	
	printf("%d\n",ans);
}

int main(){

	while (scanf("%d%d",&n,&root)==2&&(n||root)) {
		init(); work();
	}

	return 0;
}
