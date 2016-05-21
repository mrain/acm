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

int T, sum, n;

int main() {
	cin >> T;
	for (int t = 0; t < T; ++ t) {
		cin >> n;
		string s;
		cin >> s;
		int ans = 0;
		sum = s[0] - '0';
		for (int i = 1; i <= n; ++ i) {
			int now = s[i] - '0';
			if (sum < i) {
				ans += i - sum;
				sum = i;
			}
			sum += now;
		}
		printf("Case #%d: %d\n", t + 1, ans);
	}
    return 0;
}
