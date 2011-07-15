#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define maxn (100000)
#define PB push_back

vector<int> g[maxn];
int d[maxn],r[maxn];
int n,m,c;

bool check(){
	int top=0;
	c=0;
	
	bool ret=true;
	
	for (int i=1;i<=n;i++) if (!d[i]) {
		if (top) ret=false;
		d[i]=top; top=i;
	}
	
	while (top) {
		int i=top; top=d[top];
		r[++c]=i;
		
		for (int j=0;j<g[i].size();j++) {
			int x=g[i][j]; d[x]--;
			
			if (!d[x]) {
				if (top) ret=false;
				d[x]=top; top=x;
			}
		}
	}	
	
	return ret;
}

void outit(){
	for (int i=1;i<n;i++) printf("%d ",r[i]);
	printf("%d\n",r[n]);
}

int main(){
	int T; scanf("%d",&T);
	
	while (T--) {
		scanf("%d%d",&n,&m);
		
		for (int i=1;i<=n;i++) g[i].clear();
		memset(d,0,sizeof(d));
		for (int i=1;i<=m;i++) {
			int x,y; scanf("%d%d",&x,&y);
			g[x].PB(y); d[y]++;
		}
		
		bool mark=check();
		if (c<n) puts("recheck hints");
		else {
			if (!mark) puts("missing hints");
			else outit();
		}
	}

	return 0;
}
