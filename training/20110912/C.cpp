#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <cctype>

using namespace std;

#define maxn (45)
#define maxm (20)
#define MP make_pair
#define PB push_back
#define A first
#define B second

typedef pair<int, int> PII;
typedef pair<PII, int> PIII;

bool vis[maxn][maxn];
int dis[maxn][maxn], g[maxn][maxn];
int f[maxn][maxn][maxm];
int sum[maxn];
queue<PII> q;
vector<PII> e[maxn][maxn];
int n, ans;

const int dx[6] = {-1, -1, 0, 0, 1, 1}, dy[6] = {-1, 0, -1, 1, 0, 1};

void addEdge(int i, int j) {
	/*e[i][j].clear();

	for (int a = 0; a < 6; ++a) {
		int x = i + dx[a], y = j + dy[a];
		if (x > n || x <= 0) continue;
		if (y > sum[x] || y <= 0) continue;
		e[i][j].PB(MP(x, y));
	}*/
	int nn = (n + 1) >> 1;
	if (i > 1) {
		if (i > nn) {
			e[i][j].PB(MP(i - 1, j));
			e[i - 1][j].PB(MP(i, j));
			if (j < sum[i - 1]) {
				e[i][j].PB(MP(i - 1, j + 1));
				e[i - 1][j + 1].PB(MP(i, j));
			}
		} else {
			e[i][j].PB(MP(i - 1, j));
			e[i - 1][j].PB(MP(i, j));
			if (j > 1) {
				e[i][j].PB(MP(i - 1, j - 1));
				e[i - 1][j - 1].PB(MP(i, j));
			}
		}
	}
	if (j > 1) e[i][j].PB(MP(i, j - 1)), e[i][j - 1].PB(MP(i, j));
}

inline void update(int& x, int v) {
	if (x == -1 || x > v) x = v; 
}

inline void relax(int x, int y, int v) {
	if (dis[x][y] != -1 && dis[x][y] <= v) return ;
	
	dis[x][y] = v;
	if (!vis[x][y]) vis[x][y] = true; q.push(MP(x, y)); 
}

void SPFA(int mask) {
	while (!q.empty()) q.pop();
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= sum[i]; ++j) {
			dis[i][j] = f[i][j][mask], vis[i][j] = false;
			if (dis[i][j] != -1) vis[i][j] = true, q.push(MP(i, j));
		}
		
	//cout << mask << " : ========================= " << endl;
	while (!q.empty()) {
		PII now = q.front(); q.pop();
		int X = now.A, Y = now.B;
		vis[X][Y] = false;
		
		//cout << "DIS[" << X << "][" << Y << "] = " << dis[X][Y] << endl;
		
		for (int i = 0; i < e[X][Y].size(); ++i) {
			int x = e[X][Y][i].A, y = e[X][Y][i].B, v = dis[X][Y] + g[x][y];
			
			relax(x, y, v);
		}
	}
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= sum[i]; ++j)
			if (dis[i][j] != -1) update(f[i][j][mask], dis[i][j]);
}

void work() {
	for (int i = 1; i <= n; ++i) sum[i] = n + i - 1;
	for (int i = 1; i < n; ++i) sum[i + n] = n + n - i - 1;
	n = n + n - 1;
	
	memset(f, -1, sizeof(f));
	memset(g, 0, sizeof(g));
	
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= sum[i]; ++ j)
			e[i][j].clear();
			
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= sum[i]; ++j) {
			string str; cin >> str;
			
			if (isalpha(str[0])) {
				addEdge(i, j), g[i][j] = 0; 
				
				str[0] = toupper(str[0]);
				int k = 1 << (str[0] - 'A');
				f[i][j][k] = 0;
			}	
			else addEdge(i, j), g[i][j] = 1;
		}
	}
	/*
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= sum[i]; ++j) {
			cout << i << " " << j <<  " : " << endl; 
			
			for (vector<PII>::iterator it = e[i][j].begin(); it != e[i][j].end(); ++it) cout << "(" << it -> A << ", " << it -> B << ")";
			cout << endl ;
		}
	*/
	for (int k = 1; k < 16; ++k) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= sum[i]; ++j) {
				for (vector<PII>::iterator it = e[i][j].begin(); it != e[i][j].end(); ++it) {
					int x = it -> A, y = it -> B;
					for (int a = 1; a < k; ++a) {
						if ((a | k) != k) continue;
						if (f[i][j][a] == -1) continue;
						
						for (int b = 1; b < k; ++b) {
							if ((b | k) != k) continue;
							if ((a | b) != k) continue;
							if (f[x][y][b] == -1) continue;
							
							/*if (i == 5 && j == 3 && k == 12) {
								cerr << a << ' ' << b << ' ' << x << ' ' << y << endl;
							}*/							
							
							update(f[i][j][k], f[i][j][a] + f[x][y][b]);
						}
					}
				}
			}
			
		SPFA(k);
	
		/*for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= sum[i]; ++j)
				if (f[i][j][k] != -1) cout << "F[" << i << "][" << j << "][" << k << "] = " << f[i][j][k] << endl;*/

	}
	
	int ans = -1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= sum[i]; ++j)
			if (f[i][j][15] != -1) update(ans, f[i][j][15]);
	
	cout << "You have to buy " << ans << " parcels." << endl;
}

int main() {
	
	while (cin >> n && n) work();

	return 0;
}

/*
Sample Input 

4 
    B . . C 
   . . . . C 
  . A . . C . 
 . A A . . . .
  . A . . . . 
   . . . D D 
    . . . . 

0

Sample Output 

You have to buy 4 parcels.
*/
