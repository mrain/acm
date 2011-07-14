#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

int tests, n, a[1010];

int main() {
	scanf("%d", &tests);
	for (int testcase = 1; testcase <= tests; ++ testcase) {
		scanf("%d", &n);
		double ans = 0;
		for (int i = 1; i <= n; ++ i) {
			scanf("%d", a + i);
			ans += (a[i] != i);
		}
		printf("Case #%d: %6f\n", testcase, ans);
	}
	return 0;
}

