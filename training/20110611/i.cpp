#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int t, x, m, d[10000], s[10000];

int main() {
	scanf("%d%d%d", &t, &x, &m);
	int res = t;
	for (int i = 0; i < m; ++ i) {
		scanf("%d%d", d + i, s + i);
		if (!s[i]) continue;
		res = min(res, d[i] / s[i] - (d[i] % s[i] == 0 ? 1 : 0));
	}
	if (res > 0) {
		int used = res + (t - res) / 2;
		cout << (long long) x * used << endl;
	} else cout << 0 << endl;
	return 0;
}

