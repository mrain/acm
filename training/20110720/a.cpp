#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main() {
	int n;
	while (scanf("%d", &n), n) {
		int tot = 0, ma = 0, mi = 100000;
		for (int i = 0; i < n; ++ i) {
			int a;
			scanf("%d", &a);
			tot += a;
			ma = max(ma, a); mi = min(mi, a);
		}
		tot -= ma + mi;
		cout << (tot / (n - 2)) << endl;
	}
	return 0;
}
