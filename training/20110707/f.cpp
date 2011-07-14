#include <cstdio>
#include <iostream>
#include <cstdlib>
using namespace std;

int n;
long long ans;

int main() {
	while (scanf("%d", &n), n) {
		ans = 0;
		for (int i = 0; i < n; ++ i)
			ans += (n - i) * (n - i);
		cout << ans << endl;
	}
	return 0;
}
