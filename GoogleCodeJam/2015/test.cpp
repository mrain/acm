#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <sstream>
//using namespace std;

const int n = 1000000;
int upper;
bool mark[n + 10];

long long pow(int a, int k) {
	if (k == 0) return 1;
	else {
		long long ret = pow(a, k / 2);
		return ret * ret * (k % 2 == 0 ? 1 : a);
	}
}

int main() {

	mark[0] = mark[1] = true;
	upper = 1;
	for (int s = 1; ; ++ s) {
		if (pow(3, s) > n) break;
		for (int p = std::max(0, s-2); p <= s; ++ p) {
			int q = s - p;
			long long k = pow(3, p) * pow(4, q);
			if (k > n) continue;
			for (int i = upper; i >= 0; -- i) {
				if (mark[i] && i + k <= n)
					mark[i + k] = true;
			}
			upper += k;
			if (upper > n) upper = n;
		}
	}
	int ans = 0;
	for (int i = 0; i <= n; ++ i)
		if (!mark[i]) ans = i;
	std::cout << ans << std::endl;

	for (int i = 0; i <= 100; ++ i)
		if (mark[i]) std::cout << i << ' ';
	std::cout << std::endl;
    return 0;
}
