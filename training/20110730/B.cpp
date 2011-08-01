#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#include <vector>
#include <queue>

using namespace std;

#define maxn (20000)
#define MP make_pair
#define PB push_back
#define A first
#define B second

typedef pair<int,int> PII;

vector<int> g[maxn];
set<PII> f;
queue<PII> q;
int m,n;

int main(){

	while (scanf("%d%d",&n,&m)==2&&(n||m)) {
		if (!m) {
			printf("%d\n",n); continue;
		}
		
		for (int i=1;i<=n;i++) g[i].clear();
		while (!q.empty()) q.pop();
		f.clear();
		
		for (int i=0;i<m;i++) {
			int x,y; scanf("%d%d",&x,&y);
			g[x].PB(y),g[y].PB(x);
		}
		for (int i=1;i<n;i++) g[i].PB(i+1),g[i+1].PB(i);
		g[1].PB(n),g[n].PB(1);
		
		for (int i=1;i<=n;i++) sort(g[i].begin(),g[i].end());
		
		for (int i=1;i<=n;i++)
			for (int j=0;j<g[i].size();j++)
				q.push(MP(i,g[i][j]));

		int ans=0;				
		while (!q.empty()) {
			PII now=q.front(); q.pop();
			
			int cnt=0;
			while (f.find(now)==f.end()) {
				cnt++,f.insert(now);
				int x=now.A,y=now.B;
				
				vector<int>::iterator it=upper_bound(g[y].begin(),g[y].end(),x);
				if (it==g[y].end()) it=g[y].begin();
				
				now.A=y,now.B=*it;
			}
			
			if (cnt==n) cnt=0;
			ans=max(ans,cnt); 
		}
		
		printf("%d\n",ans);
	}

	return 0;
}
