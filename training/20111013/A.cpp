#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (110000)

int g[maxn];
int n, a, b;

int main() {
	int T; scanf("%d", &T);
	
	for (int t = 1; t <= T; ++t) {
		scanf("%d%d%d", &n,&a,&b); 
		for (int i = 1; i <= n; ++i) scanf("%d", &g[i]);
		sort(g + 1, g + 1 + n);
		/*
		int ans = 0, pos = 1;
		for (int i = 1; i <= n; ++i) {
			int sal = (g[i] - g[i - 1]) * b;
			
			if (pos == 1) {
				if (sal > )
			}
			else {
			
			}
		}*/
		long long ans=2LL*a+1LL*n*b;
		for(int i=2;i<=n;++i)
			if(1LL*b*(g[i]-g[i-1]-1)<2LL*a)
				ans+=1LL*b*(g[i]-g[i-1]-1);
				else ans+=2LL*a;
	
		printf("Case #%d: %I64d\n", t, ans);	
	}

	return 0;
}
