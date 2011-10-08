#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

typedef unsigned long long ULL;

ULL calc1(ULL& x) {
	ULL l = 0ll, r = 3810778ll, ret = -1ll, tot = 0ll;
	
	while (l <= r) {
		ULL mid = (l + r) / 2ll;
		
		ULL k;
		if (mid % 6ll == 0ll) k = mid / 6ll * (mid + 2ll) * (mid + 1ll);
		if (mid % 6ll == 1ll) k = (mid + 2ll) * (mid + 1ll) / 6ll * mid;
		if (mid % 6ll == 2ll) k = (mid + 1ll) * mid / 6ll * (mid + 2ll);
		if (mid % 6ll == 3ll) k = mid * (mid + 1ll) / 6ll * (mid + 2ll);
		if (mid % 6ll == 4ll) k = (mid + 2ll) / 6ll * (mid + 1ll) * mid;
		if (mid % 6ll == 5ll) k = (mid + 1ll) / 6ll * mid * (mid + 2ll);
		
		if (k < x) l = mid + 1ll, ret = mid, tot = k;
		else r = mid - 1ll;
	}
	
	x -= tot;
	return ret + 1ll;
}

ULL calc2(ULL& x) {
	ULL l = 0ll, r = 3810778ll, ret = -1ll, tot = 0ll;
	
	while (l <= r) {
		ULL mid = (l + r) / 2ll;
		
		ULL k = (mid + 1ll) * mid / 2ll;
		
		if (k < x) l = mid + 1ll, ret = mid, tot = k;
		else r = mid - 1ll;
	}
	
	x -= tot;
	return ret + 1ll;
}

int main() {
	ULL n;
	int tests;
	cin >> tests;
	while (tests --) {
		cin >> n;
		if (n <= 0ll) {
			cout << "0 0 0" << endl ;
			continue;
		}
	
		ULL i = calc1(n);
		ULL j = calc2(n);
		ULL k = n;
		
		cout << i << " " << j << " " << k << endl;
	}

	return 0;
}
