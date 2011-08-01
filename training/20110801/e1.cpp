#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <climits>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <utility>
#include <numeric>
#include <memory>
#include <stack>
#include <deque>
#include <queue>
#include <list>
#include <functional>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <bitset>

#define X first
#define Y second
#define LOW(x) ((x) & -(x))
#define SQR(x) ((x) * (x))
#define ALL(x) (x).begin(), (x).end()

using namespace std;

typedef long long ll;
typedef unsigned int ui;
typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<string> VS;

const int MAXN = 111;

int n, task, t, f[MAXN][MAXN][2], ans;
char s[MAXN];

inline int cmp(int i, int j, int k) {
	int lim = j - 1;
	while (i < lim && s[i] == '0') ++i;
	while (j < k && s[j] == '0') ++j;
	if (lim - i > k - j) return 1;
	else if (lim - i < k - j) return 0;
	for (int l = 0; l <= lim - i; ++l)
		if (s[i + l] > s[j + l]) return 1;
		else if (s[i + l] < s[j + l]) return 0;
	return -1;
}

int main(int argc, char* argv[])
{
	for (scanf("%d", &task); task--; ) {
		scanf("%d ", &n);
		gets(s);
		memset(f, 0, sizeof f);
		for (int i = 0; i < n; ++i)
			f[0][i][0] = 1;
		for (int i = 1; i < n; ++i)
			for (int j = i; j; --j)
				for (int k = j - 1; k >= 0; --k) {
					t = cmp(k, j, i);
					if (t == -1 || f[k][j - 1][t] == 0) continue;
					f[j][i][1 - t] = max(f[j][i][1 - t], f[k][j - 1][t] + 1);
				}
		ans = 0;
		for (int i = 0; i < n; ++i)
			ans = max(ans, max(f[i][n - 1][0], f[i][n - 1][1]));
		printf("%d\n", ans - 1);
	}
}
