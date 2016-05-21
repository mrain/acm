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

int s[1010], n, T;

int main() {
	cin >> T;
	for (int t = 0; t < T; ++ t) {
		cin >> n;
		int m = 0;
		for (int i = 0; i < n; ++ i) {
			cin >> s[i];
			m = max(m, s[i]);
		}
		sort(s, s + n);
		int ans = 1000;//, p = 0;
		for (int thres = 1; thres <= m; ++ thres) {
			//while (p + 1 < n && s[p] < thres) ++ p;
			int acc = 0;
			for (int i = 0; i < n; ++ i)
				acc += (s[i] - 1) / thres;
			ans = min(ans, thres + acc);
		}
		printf("Case #%d: %d\n", t + 1, ans);
	}
    return 0;
}
