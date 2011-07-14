#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, k, a[100], b[100];
vector <int> r1, r2;

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++ i)
		scanf("%d%d", a + i, b + i);
	int t = 0;
	r1.push_back(0);
	while (++ t) {
//		r2.clear();
		for (int s = 0; s < (int)r1.size(); ++ s) {
			int k = r1[s];
			r2.push_back(k);
			for (int i = 0; i < n; ++ i)
				r2.push_back(k + a[i] + b[i] * t);
		}
		sort(r2.begin(), r2.end());
		r2.erase(unique(r2.begin(), r2.end()), r2.end());
		if ((int)r2.size() > k)
			r2.erase(r2.begin() + k + 1, r2.end());
		bool flag = true;
		if ((int)r1.size() > k && (int)r2.size() > k) {
			for (int i = 0; i <= k; ++ i)
				if (r1[i] != r2[i]) {
					flag = false;
					break;
				}
		} else flag = false;
		if (flag) break;
		r1 = r2;
/*		r1.clear();
		for (int i = 0; i < (int)r2.size(); ++ i)
			if (i < (int)r2.size())
				r1.push_back(r2[i]);*/
		r2.clear();
	}
	printf("%d\n", r1[k]);
	return 0;
}

