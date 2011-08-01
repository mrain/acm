#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

#define maxn (100000)
#define PB push_back

vector<int> g[maxn];
multiset<int> f[maxn];
int v[maxn];
int n,m;

void merge(multiset<int>& a,multiset<int>& b) {
	for (multiset<int>::iterator it=b.begin();it!=b.end();it++) {
		a.insert(*it);
		
		while (a.size()>3) a.erase(a.begin());
	}
}

void dfs(int x) {
	f[x].insert(v[x]);
	
	for (int i=0;i<g[x].size();i++) {
		int k=g[x][i]; dfs(k);
		
		merge(f[x],f[k]);
	}
}

int main(){

	while (scanf("%d",&n)==1) {
		for (int i=0;i<n;i++) g[i].clear(),f[i].clear();
		
		scanf("%d",&v[0]);
		for (int i=1;i<n;i++) {
			int x; scanf("%d%d",&x,&v[i]);
			g[x].PB(i);
		}
		
		dfs(0);
		
		scanf("%d",&m);
		for (int i=0;i<m;i++) {
			int x; scanf("%d",&x);
			if (f[x].size()<3) {
				puts("-1"); continue;
			}
			
			multiset<int>::iterator it=f[x].end();
			it--; printf("%d",*it);
			it--; printf(" %d",*it);
			it--; printf(" %d\n",*it);
		}
	}

	return 0;
}
