#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int bound = 500000;
bool np[500010];
int prime[bound], pn, sum[bound + 10];

int main() {
	for (int i = 2; i <= bound; ++ i) {
		if (!np[i]) prime[pn ++] = i;
		for (int j = 0; j < pn; ++ j) {
			if ((long long)i * prime[j] > bound) break;
			np[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	for (int i = 2; i < bound + 1; ++ i)
		sum[i] = sum[i - 1] + (np[i] ? 0 : 1);
	int n;
	while (scanf("%d", &n) == 1 && n) {
		printf("%d\n", sum[2 * n] - sum[n]);
	}
	return 0;
}
