#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

typedef long long LL;

const int bound = 2000000;

bool flag[bound + 5];
vector<LL> prime;

LL calc(LL x) {
	LL r = (LL) sqrt((double) x);
	
	while (r * r < x) r++;
	while (r * r > x) r--;
	
	if (r * r == x) return 1ll;
	
	return x;
}

int main() {
	for (int i = 2; i <= bound; ++i) if (!flag[i]) {
		prime.push_back((LL) i);
		for (int k = i + i; k <= bound; k += i) flag[k] = true;
	}

	LL n; cin >> n;

	LL ans = n;
	for (int i = 0; i < prime.size(); ++i) {
		LL now = prime[i];
		
		if (now > n) break;
		
		int cnt = 0;
		while (n % now == 0ll) n /= now, cnt++;
		
		if (cnt % 2 == 1) ans /= now;
	}
	
	ans /= calc(n);
	
	cout << ans << endl;

	return  0;
}
