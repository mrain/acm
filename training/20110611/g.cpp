#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

int n;
long long f[700][700][2];
long long a[700], s[700], l[700], pos[700], tot, tota;

inline long long dist(int i, int j) {
	return min(pos[j] - pos[i], tot - pos[j] + pos[i]);
}

inline long long rpkg(int i, int j) {
	long long a = s[j], b = i > 0 ? s[i - 1] : 0;
	return tota - (a - b);
}

int main() {
	while (1) {
		cin >> n;
		if (!n) break;
		tot = tota = 0;
		for (int i = 0; i < n; ++ i) {
			cin >> a[i] >> l[i];
			a[i + n] = a[i]; l[i + n] = l[i];
			tota += a[i]; tot += l[i];
		}
		for (int i = 0; i < 2 * n; ++ i)
			s[i] = a[i] + (i > 0 ? s[i - 1] : 0);
		pos[0] = 0;
		for (int i = 0; i < 2 * n; ++ i)
			pos[i + 1] = pos[i] + l[i];
		memset(f, 0x3F, sizeof(f));
		f[0][0][0] = f[n][n][0] = f[0][0][1] = f[n][n][1] = 0;
		for (int l = 0; l < n; ++ l)
			for (int i = 0; i + l < 2 * n; ++ i) {
				int j = i + l;
				long long num = rpkg(i, j);
				for (int k = 0; k < 2; ++ k) {
					if (f[i][j][k] > 1000000000) continue;
					int pre = i - 1, suf = j + 1, now = k == 0 ? i : j;
					if (pre >= 0)
						f[pre][j][0] = min(f[pre][j][0], f[i][j][k] + num * dist(pre, now));
					if (suf < 2 * n)
						f[i][suf][1] = min(f[i][suf][1], f[i][j][k] + num * dist(now, suf));
				}
			}
		long long ans = 100000000000ll;
		for (int i = 0; i <= n; ++ i)
			ans = min(ans, min(f[i][i + n - 1][0], f[i][i + n - 1][1]));
		cout << ans << endl;
	}
	return 0;
}

