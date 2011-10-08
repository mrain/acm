#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
#include <map>

using namespace std;

#define maxn (1005)

typedef pair<int, int> PII;

PII r[maxn][maxn];
int f[maxn][maxn];
int m, n, tot;
string str[maxn*2];
int a[maxn], b[maxn];
map<string, int> hash;
char buf[maxn];

const string code_end = "#CODE-END";

void init() {
	m = n = tot = 0, hash.clear();
	
	while (gets(buf)) {
		string s(buf);
		
		if (s == code_end) break;
		
		int x = hash[s];
		if (x == 0) {
			hash[s] = x = ++tot;
			str[tot] = s;	
		}
		
		a[++m] = x;
	}
	
	while (gets(buf)) {
		string s(buf);
		
		if (s == code_end) break;
		
		int x = hash[s];
		if (x == 0) {
			hash[s] = x = ++tot;
			str[tot] = s;	
		}
		
		b[++n] = x;
	}
}

void work() {
	memset(f, -1, sizeof(f));
	
	f[m][n] = 0, r[m][n] = make_pair (m + 1, n + 1);
	
	for (int i = m ; i >= 0; --i) 
		for (int j = n; j >= 0; --j) {
			if (i == 0 && j == 0) continue;
			
			if (a[i] == b[j]) {
				if (f[i - 1][j - 1] < f[i][j] + 1 || f[i - 1][j - 1] == f[i][j] + 1 && r[i - 1][j - 1] > make_pair(i, j)) f[i-1][j-1] = f[i][j] + 1, r[i-1][j-1] = make_pair(i, j);
			}
			
			if (i != 0) {
				if (f[i - 1][j] < f[i][j] || f[i - 1][j] == f[i][j] && r[i - 1][j] > r[i][j]) f[i - 1][j] = f[i][j], r[i - 1][j] = r[i][j];
			}
			
			if (j != 0) {
				if (f[i][j - 1] < f[i][j] || f[i][j - 1] == f[i][j] && r[i][j - 1] > r[i][j]) f[i][j - 1] = f[i][j], r[i][j - 1] = r[i][j];
			}	
		}
		
	int x = 0, y = 0;
	for (int t = 1; t <= f[0][0] + 1; ++t) {
		int X = r[x][y].first, Y = r[x][y].second;
		
		if (x < X - 1 && y < Y - 1) {
			puts("//**** CONFLICT STARTS ****//");
			puts("//code in A:");
			for (int i = x + 1; i < X; ++i) puts(str[a[i]].c_str());
			puts("//code in B:");
			for (int i = y + 1; i < Y; ++i) puts(str[b[i]].c_str());
			puts("//***** CONFLICT ENDS *****//");
		}
		else  {
			if (x < X - 1) for (int i = x + 1; i < X; ++i) puts(str[a[i]].c_str());
			if (y < Y - 1) for (int i = y + 1; i < Y; ++i) puts(str[b[i]].c_str());	
		} 
		
		if (X <= m) puts(str[a[X]].c_str());
		x = X, y = Y; 
	}
}

int main() {
//printf("%d\n", sizeof(r) >> 20);
	int T; scanf("%d", &T); gets(buf);
	
	for (int t = 1; t <= T; ++t) {
		printf("Case %d:\n", t);
		
		init();
		work();
		
		puts("");
	}

	return 0;
}
