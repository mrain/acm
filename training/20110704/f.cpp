#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

int prime[800000], pc;
bool notprime[10000010];
long long n, ans;
vector <int> p;

void init_prime() {
	for (int i = 2; i < 10000000; ++ i) {
		if (!notprime[i]) prime[pc ++] = i;
		for (int j = 0; j < pc; ++ j) {
			if ((long long)i * prime[j] > 10000000) break;
			notprime[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}

void split(long long n) {
	p.clear();
	for (int i = 0; i < pc; ++ i) {
		if (n % prime[i] != 0) continue;
		int cnt = 0;
		while (n % prime[i] == 0) {
			++ cnt;
			n /= prime[i];
		}
		p.push_back(cnt);
		if (n == 1) break;
	}
	if (n != 1) p.push_back(1);
}

void dfs(int d, int limit) {
	if (d == (int)p.size()) {
		if (limit < 2147483647) ans += limit;
		return;
	}
	dfs(d + 1, limit);
	for (int i = 1; i <= p[d]; ++ i)
		dfs(d + 1, min(limit, p[d] / i));
}

int main() {
	init_prime();
	while (cin >> n && n) {
		long long print = n;
		split(n);
		ans = 0;
		dfs(0, 2147483647);
		cout << print << ' ' << ans << endl;
	}
	return 0;
}

