#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int number[300010], n;
bool isprime[300010];
int prime[300010], m;

int main() {
	for (int i = 0; 7 * i <= 300000; ++ i) {
		if (i) number[n ++] = 7 * i + 1;
		number[n ++] = 7 * i + 6;
	}
	for (int i = 0; i < n; ++ i) {
		if (!isprime[number[i]]) prime[m ++] = number[i];
		for (int j = 0; (long long)number[i] * number[j] <= 300000; ++ j) {
			isprime[number[i] * number[j]] = true;
		}
	}
	int x;
	while (scanf("%d", &x) == 1 && x > 1) {
		printf("%d:", x);
		for (int i = 0; i < m; ++ i)
			if (x % prime[i] == 0)
				printf(" %d", prime[i]);
		puts("");
	}
	return 0;
}

