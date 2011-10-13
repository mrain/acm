#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

#define maxn (100005)
#define PB push_back
#define MP make_pair

typedef pair<int, int> PII;
typedef vector<int>::iterator ITER;

vector<int> E[maxn];
map<PII, long long> H;
int n, m, q;

void outit(int x, int y, int a, long long b) {

	if (x > y) swap(x, y);
	if (a == 2) H[MP(x, y)] = b;
	
	if (b == 0ll) puts("The pair of cities are not connected or too far away.");
	else printf("%d %lld\n", a, b);
}

void work() {
	scanf("%d%d", &n, &m); H.clear();
	for (int i = 1; i <= n; ++i) E[i].clear();
	
	for (int i = 0; i < m; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		E[x].PB(y), E[y].PB(x);	
	}
	
	for (int i = 1; i <= n; ++i) sort(E[i].begin(), E[i].end());
	
	scanf("%d", &q);
	for (int i = 0; i < q; ++i) {
		int x, y; scanf("%d%d", &x, &y); 
		if (E[x].size() > E[y].size() || E[x].size() == E[y].size() && x > y) swap(x, y);
		
		if (x == y) {
			outit(x, y, 0, 1); continue;
		}
		
		if (x != y) {
			ITER it = lower_bound(E[x].begin(), E[x].end(), y);
			if (it != E[x].end() && *it == y) {
				outit(x, y, 1, upper_bound(E[x].begin(), E[x].end(), y) - it);
				continue;
			}
		}
		
		if (H.find(MP(x, y)) != H.end()) {
			outit(x, y, 2, H[MP(x, y)]); continue;
		}
		
		long long ans = 0ll;
		
		if (E[x].size() < 50) {
			for (ITER itx = E[x].begin(); itx != E[x].end(); ++itx) 
				ans += (long long) (upper_bound(E[y].begin(), E[y].end(), *itx) - lower_bound(E[y].begin(), E[y].end(), *itx));
			
			outit(x, y, 2, ans); continue;
		}
		
		for (ITER itx = E[x].begin(), ity = E[y].begin(); itx != E[x].end();) {
			int now = *itx, cntx = 0, cnty = 0;
			while (itx != E[x].end() && *itx == now) itx++, cntx++;
			while (ity != E[y].end() && *ity <= now) if (*(ity++) == now) cnty++;
			
			//printf("%d %d : %d : %d %d, %d\n", x , y, now, cntx, cnty, *ity);
			
			ans += (long long) cntx * (long long) cnty;
		}
		
		outit(x, y, 2, ans);
	}
}

int main() {
	int T; scanf("%d", &T);
	
	for (int t = 1; t <= T; ++t) {
		printf("Case #%d:\n", t);
		work();
	}

	return 0;
}
