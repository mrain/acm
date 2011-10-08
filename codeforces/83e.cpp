#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;
#define two(x) (1<<(x))

char s[200010][25];
int n, offset, m;
int p[two(21) + 10];

void update(int &a, int b) {
	if (a > b) a = b;
}

inline bool g(int i, int j, int k) {
	for (int p = 0; p < k; ++ p)
		if (s[i][m - k + p] != s[j][p])
			return false;
	return true;
}

inline void apply(int i, int res) {
	int val = 0;
	for (int j = 0; j <= m; ++ j) {
		if (j && s[i][m - j] == '1') val |= two(j - 1);
		update(p[val | two(j)], res - offset);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i)
		scanf("%s", s[i]);
	m = strlen(s[0]);
	memset(p, 0x3F, sizeof(p));

	p[1] = m;
	for (int i = 1; i < n; ++ i) {
		int k = m, val = 1, res = p[1] + offset + m;
		while (k && !g(i - 1, i, k)) -- k;

		for (int j = 0; j < m; ++ j) {
			val = (val << 1) | ((int)s[i][j] - '0');
			update(res, p[val] + offset + m - j - 1);
		}

		offset += m - k;
		apply(i - 1, res);
		i = i - 1 + res - res + 1;
	}

	int ans = 2147483647;
	for (int i = 2; i < two(m + 1); ++ i)
		ans = min(ans, p[i] + offset);
	if (n == 1) ans = m;
	cout << ans << endl;

	return 0;
}

