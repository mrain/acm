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

int T, n;
int a[10010];

int main() {
	cin >> T;
	for (int t = 1; t <= T; ++ t) {
		cin >> n;
		for (int i = 0; i < n; ++ i) cin >> a[i];
		int A = 0, B = 0, k = 0;
		for (int i = 1; i < n; ++ i) {
			if (a[i] < a[i - 1]) {
				A += a[i - 1] - a[i];
				k = max(k, a[i - 1] - a[i]);
			}
		}
		for (int i = 0; i < n - 1; ++ i) {
			B += min(k, a[i]);
		}
		printf("Case #%d: %d %d\n", t, A, B);
	}
    return 0;
}
