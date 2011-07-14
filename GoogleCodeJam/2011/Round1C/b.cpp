#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int tests, n, c, l, sz;
long long t;
long long s[1000010], a[1010], chosen[1000010];

int main() {
	cin >> tests;
	int ca = 0;
	while (tests --) {
		cout << "Case #" << ++ ca << ": ";
		cin >> l >> t >> n >> c;
		for (int i = 0; i < c; ++ i) cin >> a[i];
		s[0] = 0;
		for (int i = 1; i <= n; ++ i)
			s[i] = s[i - 1] + a[(i - 1) % c];
		long long stop = t / 2;
		sz = 0;
		for (int i = 0; i <= n; ++ i)
			if (s[i] >= stop)
				chosen[sz ++] = s[i] - max(s[i - 1], stop);
		sort(chosen, chosen + sz);
		reverse(chosen, chosen + sz);
		sz = min(sz, l);
		s[n] *= 2;
		for (int i = 0; i < sz; ++ i)
			s[n] -= chosen[i];
		cout << s[n] << endl;
	}
	return 0;
}

