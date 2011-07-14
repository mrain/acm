#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

double res;
int maxs, mins, tot, a;

int calc(int n) {
	int res = 0;
	n *= 10;
	res = n / 4;
	if (n % 4 != 0) res = res * 10 + calc(n % 4);
	return res;
}

int main() {
	while (true) {
		maxs = tot = a = 0;
		mins = 2147483647;
		for (int i = 0; i < 6; ++ i) {
			scanf("%d", &a);
			maxs = max(maxs, a);
			mins = min(mins, a);
			tot += a;
		}
		if (tot == 0) break;
		tot -= maxs + mins;
		printf("%d", tot / 4);
		if (tot % 4 != 0) printf(".%d", calc(tot % 4));
		puts("");
	}
	return 0;
}

