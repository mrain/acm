#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int bound = 10000000;

typedef unsigned long long ULL;

bool notprime[bound];
int prime[3000000], cnt;

unsigned long long Get(unsigned long long a, unsigned long long n) {
	if (n < a) return 0;
	unsigned long long res = Get(a, n / a);
	return res + n / a;
}

ULL calc(ULL x, ULL v) {
	return x == 0ll ? 0ll : x / v + calc(x / v, v);
}

int main() {
	for (int i = 2; i < bound; ++ i) {
		if (!notprime[i]) prime[cnt ++] = i;
		for (int j = 0; j < cnt; ++ j) {
			if ((long long)i * prime[j] >= bound) break;
			notprime[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	
	int T; cin >> T;// T = 500;
	for (int cases = 1; cases <= T; ++cases) {
		cout << "Case " << cases << ": ";
	
		ULL n, k; cin >> n >> k;// n = 1000000000000000000llu, k = 222222223llu;
		
		if (k == 1ll) {
			cout << "inf" << endl; continue;
		}
		
		ULL ans = 6000000000000000000llu;
		
		for (int i = 0; i < cnt && k > 1ll; ++i) {
			ULL now = prime[i];
			if (k % now != 0ll) continue;
			ULL cnt = 0ll;
			while (k % now == 0) cnt++, k /= now;
			ans = min(ans, calc(n, now) / cnt);
		} 
		
		if (k > 1ll) ans = min(ans, calc(n, k));
		
		cout << ans << endl;
	}
	
	
	//cout << Get(2, 1000000000000000000ll) << endl;
	return 0;
}
