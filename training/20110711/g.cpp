#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int tests;
char buf[200000];
vector <string> s;
int n, m;

void init() {
	int l = strlen(buf);
	buf[l ++] = ';'; buf[l] = 0;
	int start = 0; m = 0;
	s.clear();
	for (int i = 0; i < l; ++ i)
		if (buf[i] == ';') {
			string tmp(buf + start, buf + i);
			reverse(tmp.begin(), tmp.end());
			s.push_back(tmp);
			m = max(m, (int)tmp.length());
			start = i + 1;
		}
	reverse(s.begin(), s.end());
	n = (int)s.size();
}

int f[300][300], p[300][300];
string ans[300][300];

inline char get(const string &a, int rotate, int pos) {
	pos = (pos + rotate + 2 * a.length()) % (int)a.length();
	return a[pos];
}

/*inline int calc(const string &a, int x, const string &b, int y) {
	int ret = 0, mp = min(a.length(), b.length());
	while (ret < mp && get(a, x, -ret - 1) == get(b, y, ret)) ++ ret;
	return ret;
}*/

int calc(const string &s2, int r2, const string &s1, int r1) {
	int ret=0;

	static int next[200],suf[200];
	
	memset(next,0,sizeof(next)),memset(suf,0,sizeof(suf));
	
	int m=s1.length(),n=s2.length();
	
	int k=0,j,p=0; next[1]=m,next[0]=0;

	for (int i=2;i<=m;i++) {
		j=next[i-k+1];
		if (i+j-1>p) j=p-i+1;
		if (j<=0) j=0;
		
		while (j+i<=m&&get(s1,r1,j)==get(s1,r1,i+j-1)) j++;
		
		next[i]=j;
		if (j+i>p) p=i+j-1,k=i;
	}
	
	k=p=0,suf[0]=0;
	for (int i=1;i<=n;i++) {
		j=next[i-k+1];
		if (i+j-1>p) j=p-i+1;
		if (j<0) j=0;
		
		while (j+i<=n&&j<m&&get(s2,r2,j+i-1)==get(s1,r1,j)) j++;
		
		suf[i]=j;
		if (j+i>p) p=i+j-1,k=i;
		
		if (suf[i]==n-i+1) ret=max(ret,n-i+1);
	}
	
	return ret;
}


inline bool cmp(int i, int a, int b) {
	if (a == -1) return false;
	if (b == -1) return true;
	int l = min(ans[i][a].length(), ans[i][b].length());
	for (int i = 0; i < l; ++ i) {
		char ca = ans[i][a][ans[i][a].length() - i - 1];
		char cb = ans[i][b][ans[i][b].length() - i - 1];
		if (ca == cb) continue;
		return ca < cb;
	}
	return true;
//	return ans[i][a] < ans[i][b];
/*	int l = (int)s.length();
	for (int i = 0; i < l; ++ i) {
		char ca = get(s, a, i), cb = get(s, b, i);
		if (ca == cb) continue;
		return ca < cb;
	}
	return true;*/
}

void work() {
	memset(f, 0x1F, sizeof(f));
	memset(p, 0xFF, sizeof(p));
	for (int i = 0; i < (int)s[0].length(); ++ i) {
		f[0][i] = s[0].length();
		ans[0][i] = "";
		for (int j = 0; j < (int)s[0].length(); ++ j)
			ans[0][i] += get(s[0], i, j);
	}
	for (int i = 1; i < n; ++ i)
		for (int j = 0; j < 200; ++ j)
			ans[i][j] = "";
	for (int i = 1; i < n; ++ i) {
		int xx = (int)s[i - 1].length();
		int yy = (int)s[i].length();
		for (int j = 0; j < xx; ++ j)
			for (int k = 0; k < yy; ++ k) {
				int cost = calc(ans[i - 1][j], 0, s[i], k);
				if (f[i][k] > f[i - 1][j] + yy - cost) {
					f[i][k] = f[i - 1][j] + yy - cost;
					ans[i][k] = ans[i - 1][j];
					for (int q = cost; q < yy; ++ q)
						ans[i][k] += get(s[i], k, q);
					p[i][k] = j;
				} else if (f[i][k] == f[i - 1][j] + yy - cost) {
					if (cmp(i - 1, j, p[i][k])) {
						ans[i][k] = ans[i - 1][j];
						for (int q = cost; q < yy; ++ q)
							ans[i][k] += get(s[i], k, q);
						p[i][k] = j;
					}
				}
			}
	}
}

int main() {
	scanf("%d", &tests);
	while (tests --) {
		scanf("%s", buf);
		init();
		work();
		int k = 0, cur = n - 1;
		for (int i = 1; i < (int)s[cur].length(); ++ i)
			if (f[cur][i] < f[cur][k]
			|| (f[cur][i] == f[cur][k] && cmp(cur, i, k)))
				k = i;
//		reverse(output.begin(), output.end());
//		cout << output.length() << endl;
		reverse(ans[cur][k].begin(), ans[cur][k].end());
//		cout << ans[cur][k].length() << endl;
		cout << ans[cur][k] << endl;
	}
	return 0;
}

