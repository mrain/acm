#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#define two(x) (1 << (x))
using namespace std;

int tests, n;
map <string, int> man, woman;
char buf[20000];
string m[20], wm[20];
bool prefer[20][20];
long long f[two(18)];
int bitcnt[two(18)];

void init() {
	man.clear(); woman.clear();
	memset(prefer, 0, sizeof(prefer));
	gets(buf);
	sscanf(buf, "%d", &n);
	gets(buf);
	int l = strlen(buf), pre = 0, cnt = 0;
	buf[l] = ' ', buf[++ l] = 0;
	for (int i = 0; i < l; ++ i)
		if (buf[i] == ' ') {
			m[cnt ++] = string(buf + pre, buf + i);
			pre = i + 1;
		}
	sort(m, m + n);
	reverse(m, m + n);
	for (int i = 0; i < n; ++ i)
		man[m[i]] = i;
	gets(buf);
	l = strlen(buf), pre = 0, cnt = 0;
	buf[l] = ' ', buf[++ l] = 0;
	for (int i = 0; i < l; ++ i)
		if (buf[i] == ' ') {
			wm[cnt ++] = string(buf + pre, buf + i);
			pre = i + 1;
		}
	sort(wm, wm + n);
	for (int i = 0; i < n; ++ i)
		woman[wm[i]] = i;
	for (int i = 0; i < n; ++ i) {
		gets(buf);
		l = strlen(buf), cnt = 0;
		buf[l] = ' ', buf[++ l] = 0;
		int stop = 0;
		while (buf[stop] != ':') ++ stop;
		int id = man[string(buf, buf + stop)];
		pre = stop + 2;
		for (int j = stop + 2; j < l; ++ j)
			if (buf[j] == ' ') {
				int a = woman[string(buf + pre, buf + j)];
				prefer[id][a] = true;
				pre = j + 1;
			}
	}
}

int main() {
	gets(buf);
	sscanf(buf, "%d", &tests);
	int ca = 0;
	for (int i = 1; i < two(16); ++ i)
		bitcnt[i] = bitcnt[i - (i & (-i))] + 1;
	while (tests --) {
		init();
		memset(f, 0, sizeof(f));
		f[0] = 1;
		for (int s = 1; s < two(n); ++ s) {
			int i = bitcnt[s] - 1;
			for (int j = 0; j < n; ++ j)
				if ((two(j) & s) != 0 && prefer[i][j])
					f[s] += f[s ^ two(j)];
		}
		cout << "Case " << ++ ca << ":" << endl;
		if (f[two(n) - 1] == 0) cout << "No Way" << endl;
		else {
			int now = two(n) - 1;
			cout << f[now] << endl;
			for (int i = n - 1; i >= 0; -- i) {
				cout << m[i] << ' ';
				for (int j = 0; j < n; ++ j)
					if (prefer[i][j] && (two(j) & now) != 0 && f[now - two(j)] > 0) {
						cout << wm[j];
						now -= two(j);
						if (i) cout << ' ';
						break;
					}
			}
			cout << endl;
		}
	}
	return 0;
}

