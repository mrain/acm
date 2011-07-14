#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

#define MP make_pair
#define PB push_back
#define LB lower_bound
#define UB upper_bound

const double eps = 1e-8;
const double pi = acos(-1.0);

int n, m, sl[110], sr[110], su[110], sd[110], s[110][110], k, a1, a2;
void work()
{
	for (int i = 0; i <= 105; i++)
		sl[i] = sr[i] = su[i] = sd[i] = 192837465;
	for (int i = 15 + 1; i <= n; i++)
		for (int j = 28 + 1; j <= m; j++) {
			int now = s[i - 1][j - 1] - s[i - 15][j - 1] - s[i - 1][j - 28] + s[i - 15][j - 28];
			sl[i] = min(sl[i], now);
			sr[i - 15] = min(sr[i - 15], now);
			su[j - 28] = min(su[j - 28], now);
			sd[j] = min(sd[j], now);
		}
	for (int i = 28 + 1; i <= n; i++)
		for (int j = 15 + 1; j <= m; j++) {
			int now = s[i - 1][j - 1] - s[i - 28][j - 1] - s[i - 1][j - 15] + s[i - 28][j - 15];
			sl[i] = min(sl[i], now);
			sr[i - 28] = min(sr[i - 28], now);
			su[j - 15] = min(su[j - 15], now);
			sd[j] = min(sd[j], now);
		}
	for (int i = 1; i <= n; i++)
		sl[i] = min(sl[i], sl[i - 1]);
	for (int i = n; i; i--)
		sr[i] = min(sr[i], sr[i + 1]);
	for (int i = m; i; i--)
		su[i] = min(su[i], su[i - 1]);
	for (int i = 1; i <= m; i++)
		sd[i] = min(sd[i], sd[i - 1]);
	int ans = 192837465;
	for (int i = n; i; i--) {
//		cout << sl[i] << ' ' << sr[i] << endl;
		ans = min(ans, sl[i] + sr[i]);
	}
	for (int i = m; i; i--) {
//		cout << su[i] << ' ' << sd[i] << endl;
		ans = min(ans, su[i] + sd[i]);
	}
	printf("%d\n", ans);
}
int main()
{
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	while (scanf("%d%d", &n, &m) == 2 && n + m) {
		scanf("%d", &k);
		n++, m++;
		memset(s, 0, sizeof(s));
		for (int i = 1; i <= k; i++) {
			scanf("%d%d", &a1, &a2);
			a1++, a2++;
			s[a1][a2]++;
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				s[i][j] = s[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
		work();
	}
}
