#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int tests, n, l, h, a[101];

bool valid(int x) {
	for (int i = 0; i < n; ++ i)
		if (x % a[i] != 0 && a[i] % x != 0)
			return false;
	return true;
}

int main() {
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		printf("Case #%d: ", ++ ca);
		scanf("%d%d%d", &n, &l, &h);
		for (int i = 0; i < n; ++ i) scanf("%d", a + i);
		bool found = false;
		for (int x = l; x <= h; ++ x)
			if (valid(x)) {
				printf("%d\n", x);
				found = true;
				break;
			}
		if (!found) puts("NO");
	}
	return 0;
}

