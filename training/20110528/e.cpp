#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;

const int limit = 1000000;
bool notprime[limit + 10], avaiable[limit + 10], square[limit + 10];
int prime[limit + 10], pcount, sum1[limit + 10], sum2[limit + 10];

void gen_prime() {
	pcount = 0;
	for (int i = 2; i < limit; ++ i) {
		if (!notprime[i]) prime[pcount ++] = i;
		for (int j = 0; j < pcount; ++ j) {
			if ((long long)i * prime[j] > limit) break;
			notprime[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}

bool check(int p) {
	for (int i = 1; i * i < p; ++ i)
		if (square[p - i * i]) return true;
	return false;
}

int main() {
	gen_prime();
	for (int i = 1; i * i < limit; ++ i)
		square[i * i] = true;
	for (int i = 2; i <= limit; ++ i)
		sum1[i] = sum1[i - 1] + (!notprime[i] ? 1 : 0);
	for (int i = 0; i < pcount; ++ i) {
		if (check(prime[i])) avaiable[prime[i]] = true;
	}
	for (int i = 2; i <= limit; ++ i)
		sum2[i] = sum2[i - 1] + (avaiable[i] ? 1 : 0);
	int l, u;
	while (true) {
		scanf("%d%d", &l, &u);
		if (l == -1 && u == -1) break;
		int a = l, b = u;
		if (a < 1) a = 1;
		if (b < 1) b = 1;
		printf("%d %d %d %d\n", l, u, sum1[b] - sum1[a - 1], sum2[b] - sum2[a - 1]);
	}
	return 0;
}

