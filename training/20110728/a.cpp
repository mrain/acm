#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int a[101], b[101], n, m, sa, sb;

int main() {
	while (scanf("%d%d", &n, &m) == 2 && n + m) {
		sa = 0, sb = 0;
		for (int i = 0; i < n; ++ i) scanf("%d", a + i), sa += a[i];
		for (int i = 0; i < m; ++ i) scanf("%d", b + i), sb += b[i];
		int a1 = 1000, a2 = 1000;
		for (int i = 0; i < n; ++ i)
			for (int j = 0; j < m; ++ j) {
				if (sa + b[j] - a[i] != sb + a[i] - b[j]) continue;
				if (a[i] + b[j] < a1 + a2)
					a1 = a[i], a2 = b[j];
			}
		if (a1 == 1000) puts("-1");
		else printf("%d %d\n", a1, a2);
	}
	return 0;
}

