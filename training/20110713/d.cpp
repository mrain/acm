#include <cstdio>
#include <set>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int a[300], n, tot;
vector <int> f[300];
set <int> hash[300];

void getans(int p, int &a1, int &a2) {
	for (int i = 0; i < (int)f[p].size(); ++ i) {
		int a = f[p][i], b = tot - a;
		if (a > b) swap(a, b);
		if (b - a < a2 - a1) a1 = a, a2 = b;
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i)
		scanf("%d", a + i), tot += a[i];
	sort(a, a + n);
	reverse(a, a + n);
	f[0].push_back(0);
	hash[0].insert(0);
	int upper = n / 2 + (n % 2);
	for (int i = 0; i < n; ++ i) {
	//	cout << i << endl;
		int lower = max(0, (n / 2) - (n - i));
		for (int j = n - 1; j >= 0; -- j) {
			if (j > upper) continue;
			if (j < lower) break;
			for (int k = 0; k < (int)f[j].size(); ++ k) {
				int d = a[i] + f[j][k];
				if (hash[j + 1].find(d) == hash[j + 1].end()) {
					f[j + 1].push_back(d);
					hash[j + 1].insert(d);
				}
			}
		}
	}
	int ans1 = 0, ans2 = 200000;
	getans(n / 2, ans1, ans2);
	if (n & 1) getans(n / 2 + 1, ans1, ans2);
	cout << ans1 << ' ' << ans2 << endl;
	return 0;
}
