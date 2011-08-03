#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define maxn (10000)
#define PB push_back

vector<int> g[maxn];
int flag[maxn];
int n;

char buf[10];

int main(){
	int T; scanf("%d",&T);
	
	while (T--) {
		scanf("%d",&n);
		
		int maxt=0;
		for (int i=0;i<n;i++) {
			int x,y; scanf("%s%d%d",buf,&x,&y);
			g[x].PB(i),g[y].PB(i),maxt=max(maxt,max(x,y));
		}
		
		int sum=0;
		for (int i=0;i<=maxt;i++) {
			for (int j=0;j<g[i].size();j++) {
				int k=g[i][j];
				
				if (flag[k]&1) sum--,flag[k]^=1;
				else sum++,flag[k]^=1;
			}
			
			if (sum) putchar('A'+sum-1);
		}
		
		puts("");
		
		for (int i=0;i<=maxt;i++) g[i].clear();
	}

	return 0;
}
