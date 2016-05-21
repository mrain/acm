#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

int tests;
bool bits[10];

int main() {
	cin >> tests;
	for (int t = 1; t <= tests; ++ t) {
		int n;
		cin >> n;
		if (n == 0) {
			printf("Case #%d: INSOMNIA \n", t);
			continue;
		}
		memset(bits, 0, sizeof(bits));
		int cnt = 0;
		long long now = 0;
		bool mark = false;
		do {
			now += n; ++ cnt; mark = true;
			long long tmp = now;
			while (tmp) {
				bits[tmp % 10] = 1;
				tmp /= 10;
			}
			for (int i = 0; i < 10; ++ i)
				if (!bits[i]) {
					mark = false;
					break;
				}
		} while (cnt <= max(100, n) && !mark);
		if (mark) printf("Case #%d: %lld\n", t, now);
		else printf("Case #%d: INSOMNIA \n", t);
	}
    return 0;
}
