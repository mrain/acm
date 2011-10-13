#include <cstdio>
#include <set>

using namespace std;

int g[300][300];

int main() {
	int T; scanf("%d", &T);

	for (int t = 1; t <= T; ++t) {
		printf("Case #%d:\n", t);
		
		int n; scanf("%d", &n);
		
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				g[i][j] = (j - 1) * n + i;
				
		for (int j = 1; j < n; ++j) {
			swap(g[1][j], g[2][j]);
			for(int i=3;n+3-i>i;++i)
				swap(g[i][j],g[n+3-i][j]);
		}
		swap(g[1][1], g[1][n]);
		
		for (int i = 1; i <= n; ++i) 
			for (int j = 1; j <= n; ++j)
				printf("%d%c", g[i][j], j == n ? '\n' : ' ' );
	}

/*
	for (int k = 3; k <= 200; ++k) {
		int n = k;
	
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				g[i][j] = (j - 1) * n + i;
				
		for (int j = 1; j < n; ++j) {
			swap(g[1][j], g[2][j]);
			for(int i=3;n+3-i>i;++i)
				swap(g[i][j],g[n+3-i][j]);
		}
		swap(g[1][1], g[1][n]);
		
		set<int> f; f.clear();
		
		for (int i = 1; i <= n; ++i) {
			int cnt = 0;
			
			for (int j = 1; j <= n; ++j) cnt += g[i][j];
			
			if (f.find(cnt) != f.end()) printf("WA %d\n", k);
			else f.insert(cnt);
		} 
		
		for (int i = 1; i <= n; ++i) {
			int cnt = 0;
			
			for (int j = 1; j <= n; ++j) cnt += g[j][i];
			
			if (f.find(cnt) != f.end()) printf("WA %d\n", k);
			else f.insert(cnt);
		}
		
		int cnt = 0;
		for (int i = 1; i <= n; ++i) cnt += g[i][i];
		if (f.find(cnt) != f.end()) printf("WA %d\n", k);
		else f.insert(cnt);
		
		cnt = 0;
		for (int i = 1; i <= n; ++i) cnt += g[n - i + 1][i];
		if (f.find(cnt) != f.end()) printf("WA %d\n", k);
		else f.insert(cnt);
	}
*/
	return 0;
}
