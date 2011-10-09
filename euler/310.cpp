#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int bound;
int sg[100010], cnt[100010], m;
int vis[100010];

long long C(long long a, int t) {
	long long res = 1;
	for (int i = 0; i < t; ++ i) {
		res *= (a - i);
		res /= (i + 1);
	}
	return res;
}

int main() {
	bound = 100000;
	sg[0] = 0; cnt[0] = 1;
	for (int i = 1; i <= bound; ++ i) {
		for (int j = 1; j * j <= i; ++ j)
			vis[sg[i - j * j]] = i;
		while (vis[sg[i]] == i) ++ sg[i];
		++ cnt[sg[i]];
		m = max(m, sg[i]);
	}
	long long ans = 0;
	for (int sga = 0; sga <= m; ++ sga)
		for (int sgb = 0; sgb <= m; ++ sgb)
			if (sga != sgb && sga != (sga ^ sgb) && sgb != (sga ^ sgb))
				ans += (long long)cnt[sga] * cnt[sgb] * cnt[sga ^ sgb];
	ans /= 6;
	for (int sga = 1; sga <= m; ++ sga)
		ans += (C(cnt[sga], 2) + cnt[sga]) * cnt[0];
	ans += C(cnt[0], 3) + C(cnt[0], 2) * 2 + cnt[0];
//	cout << C(cnt[0], 3) + C(cnt[0], 2) * 2 + cnt[0] << endl;
	cout << ans << endl;
/*	ans = 0;
	long long A = 0;
	for (int i = 0; i <= bound; ++ i)
		for (int j = i; j <= bound; ++ j)
			for (int k = j; k <= bound; ++ k)
				if ((sg[i] ^ sg[j] ^ sg[k]) == 0) {
					if (sg[i] == sg[j] && sg[i] == sg[k] && sg[j] == sg[k])
						++ A;
					++ ans;
				}
	cout << A << endl;
	cout << ans << endl;*/
	return 0;
}
