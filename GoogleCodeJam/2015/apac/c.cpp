#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

map <string, int> pool;
int g[100][100];
int tests;
int n, q;

int get(const string &a) {
	if (pool.count(a) == 0) {
		pool.insert(make_pair(a, pool.size()));
	}
	return pool[a];
}

int invalid = 0x3F3F3F3F;

int main() {
	cin >> tests;
	for (int cases = 1; cases <= tests; ++ cases) {
		memset(g, 0x3F, sizeof(g));
		pool.clear();
		cin >> n;
		for (int ttt = 0; ttt < n; ++ ttt) {
			string sa, sb, str;
			cin >> str;
			int tt = 0;
			for (tt = 0; tt < str.length(); ++ tt) {
				if (str[tt] == '+') break;
				sa += str[tt];
			}
			for (++ tt; tt < str.length(); ++ tt) {
				if (str[tt] == '=') break;
				sb += str[tt];
			}
			int val = 0, mp = 1;
			++ tt;
			if (str[tt] == '-') {
				mp = -1;
				++ tt;
			}
			for (; tt < str.length(); ++ tt) {
				val = val * 10 + (str[tt] - '0');
			}
			int a = get(sa), b = get(sb);
			g[a][b] = g[b][a] = val * mp;
		}
		int m = pool.size();

		int cnt = 0;
		//do {
			cnt = 0;
			for (int a = 0; a < m; ++ a)
				for (int b = 0; b < m; ++ b) {
					if (g[a][b] == invalid) continue;
					for (int i = 0; i < m; ++ i) {
						for (int j = 0; j < m; ++ j) {
							if (g[i][j] == invalid && g[i][a] != invalid && g[b][j] != invalid) {
								++ cnt;
								g[i][j] = g[j][i] = g[i][a] + g[b][j] - g[a][b];
							}
						}
					}
				}
		//} while (cnt > 0);
		cin >> q;
		cout << "Case #" << cases << ":" << endl;
		for (int ttt = 0; ttt < q; ++ ttt) {
			string sa, sb, str;
			cin >> str;
			int tt = 0;
			for (tt = 0; tt < str.length(); ++ tt) {
				if (str[tt] == '+') break;
				sa += str[tt];
			}
			for (++ tt; tt < str.length(); ++ tt) {
				if (str[tt] == '=') break;
				sb += str[tt];
			}
			int a = get(sa), b = get(sb);
			/*cerr << sa << " " << a << endl;
			cerr << sb << " " << b << endl;
			cerr << g[a][b] << " " << g[b][a]  << endl;*/
			if (a < m && b < m && g[a][b] != invalid)
				cout << sa << "+" << sb << "=" << g[a][b] << endl;
		}
	}
    return 0;
}
