#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1 << 20;
int n, f[N + 5];

void dfs(int l, int r) {
	if (l == r) return ;
	
	int mid = (l + r) >> 1;
	
	dfs(l, mid), dfs(mid + 1, r);
	
	for (int i = 0; i <= mid - l; ++i) f[mid + 1 + i] += f[l + i]; 
}

int main(){
	for(;;){
		scanf("%d", &n);
		if (n < 0) break;
		
		memset(f, 0, sizeof(f));
		
		for (int i = 0; i < n; ++i) {
			int x, v; scanf("%d%d", &x, &v); f[x] += v;
		}
		
		dfs(0, N - 1);
		
		int ans = 0;
		for (int i = 0; i < N; ++i) ans = max(ans, f[i]);
		
		printf("%d\n",ans);
	}
	
	return 0;
}
