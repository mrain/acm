#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int limit = 1000000;
int prime[limit], pn;
bool notprime[limit + 10];

void genp() {
	for (int i = 2; i < limit; ++ i) {
		if (!notprime[i]) prime[pn ++] = i;
		for (int j = 0; j < pn; ++ j) {
			if ((long long)i * prime[j] >= limit) break;
			notprime[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}

long long n, m, k, left;
int cnt[limit];

int main() {
	genp();
	cin >> m;
	for (int i = 0; i < pn; ++ i) {
		cnt[i] = 0;
		while (m % prime[i] == 0) ++ cnt[i], m /= prime[i];
	}
	for (int i = 0; i < pn; ++ i) {
	}
	return 0;
}
