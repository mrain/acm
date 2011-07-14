#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

int n, a[1010], tests;

int main() {
	scanf("%d", &tests);
	for (int testcase = 1; testcase <= tests; ++ testcase) {
		scanf("%d", &n);
		int valid = 0, sum = 0, del = 10000000;
		for (int i = 0; i < n; ++ i) {
			scanf("%d", a + i);
			valid ^= a[i];
			sum += a[i];
			del = min(del, a[i]);
		}
		if (valid) {
			printf("Case #%d: NO\n", testcase);
			continue;
		}
		printf("Case #%d: %d\n", testcase, sum - del);
	}
	return 0;
}

