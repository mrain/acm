#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int n, mile, juice;
int tests;

int main() {
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		scanf("%d", &n);
		mile = juice = 0;
		for (int i = 0; i < n; ++ i) {
			int a;
			scanf("%d", &a);
			mile += ((a / 30) + 1) * 10;
			juice += ((a / 60) + 1) * 15;
		}
		printf("Case %d:", ++ ca);
		if (mile <= juice) printf(" Mile");
		if (juice <= mile) printf(" Juice");
		printf(" %d\n", min(mile, juice));
	}
	return 0;
}

