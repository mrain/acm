#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (20)

bool flag[maxn];
int g[maxn][maxn], G[maxn][maxn];
int m, n, ans;
char buf[100];
const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

inline void change(const int& x, const int& y) {
	for (int i = 0; i < 4; ++i) g[x + dx[i]][y + dy[i]] ^= 1;
	g[x][y] ^= 1;
}

void check() {
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j)
			g[i][j] = G[i][j];
			
	int cnt = 0;
	for (int i = 1; i <= n && cnt < ans; ++i) if (flag[i]) cnt++, change(1, i);
	
	for (int i = 2; i <= m && cnt < ans; ++i)
		for (int j = 1; j <= n && cnt < ans; ++j) 
			if (g[i - 1][j]) cnt++, change(i, j);
			
	for (int i = 1; i <= n; ++i) if (g[m][i]) return ;
			
	ans = min(ans, cnt);
}

void dfs(int x) {
	if (x > n) {
		check(); return ;
	}
	
	flag[x] = false;
	dfs(x + 1);
	flag[x] = true;
	dfs(x + 1);
}

void work() {
	for (int i = 0; i < m; ++i) {
		scanf("%s", buf);
		for (int j = 0; j < n; ++j) G[i + 1][j + 1] = (buf[j] == '.') ? 0 : 1;	
	}
/*	
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) putchar('0' + G[i][j]);
		puts("");
	}
*/	
	ans = 300;
	dfs(1);
	
	if (ans == 300) puts("Damaged billboard.");
	else printf("You have to tap %d tiles.\n", ans);
}

int main() {
	while (scanf("%d%d", &m, &n) == 2 && (m || n)) work();
	
	return 0;
}

/*
Sample Input 

5 5 
XX.XX 
X.X.X 
.XXX. 
X.X.X 
XX.XX 

5 5 
.XX.X 
..... 
..XXX 
..X.X 
..X.. 

1 5 
...XX 

5 5 
...X. 
...XX 
.XX.. 
..X.. 
..... 

8 9 
..XXXXX.. 
.X.....X. 
X..X.X..X 
X.......X 
X.X...X.X 
X..XXX..X 
.X.....X. 
..XXXXX.. 

0 0

Sample Output 

You have to tap 5 tiles. 
Damaged billboard. 
You have to tap 1 tiles. 
You have to tap 2 tiles. 
You have to tap 25 tiles.
*/
