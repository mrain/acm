#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m, a[200000], s;
long long ans;

int main() {
	scanf("%d%d", &n, &m);
	s = 0;
	for (int i = 0; i < m; ++ i) {
		scanf("%d", a + i);
		if (a[i] > 1) s += a[i] - 2;
		else s += a[i];
	}
	ans = 0;
	for (int i = 0; i < m; ++ i)
		if (a[i] > 1)
			ans += s + 1, s += 2;
	cout << ans << endl;
	return 0;
}

