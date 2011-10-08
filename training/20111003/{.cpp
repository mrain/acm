#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>

using namespace std;

#define maxn (110000)

const int bound = 35000;

map< int, multiset<int> > f;
int g[maxn], fac[maxn];
bool flag[maxn];
int m;

void add(int x, bool mark) {
	for (int i = 0; i < m && x > 1; ++i) if (x % fac[i] == 0) {
		int cnt = 0; 
		while (x % fac[i] == 0) cnt++, x /= fac[i]; 
		
		if (mark) {
		
		}
		else 
	}
}

int main() {
	for (int i = 2; i <= bound; ++i) if (!flag[i]) {
		for (int k = i; k <= bound; k += i) flag[k] = true;
		fac[m++] = i;
	} 	
	
	printf("%d\n", m);

	int n; scanf("%d", &n);
	
	int tot = 0;
	for (int i = 0; i <= n; ++i) g[i] = 1;
	for (int i = 0; i < n; ++i) {
		int now; scanf("%d", &now);
			
		if (now > 0) {
			tot++, add(now, true);
		}
		else {
			tot--, add(now, false);
		}
		
		printf("%d\n", g[tot]);
	}

	return 0;
}
