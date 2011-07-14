#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

int n;
vector <int> l[1000];

int main() {
	bool first = true;
	while (scanf("%d", &n)) {
		if (!n) break;
		if (!first) puts("");
		first = false;
		int cnt = n * (n + 1) / 2;
		if (cnt & 1) {
			puts("0");
		} else {
			printf("%d\n", n);
			for (int i = 1; i <= n; ++ i) {
				l[i].clear();
				for (int k = i; k <= n; ++ k)
					l[i].push_back(k);
				reverse(l[i].begin(), l[i].end());
			}
			for (int i = 1; i <= n; ++ i) {
				if ((l[i].size() & 1) == 1) {
					int p = l[i].back();
					l[i].pop_back();
					l[i + 2].push_back(p);
				}
				reverse(l[i].begin(), l[i].end());
			}
			sort(l + 1, l + n + 1);
			for (int i = 1; i <= n; ++ i) {
				for (int k = 0; k < (int)l[i].size() - 1; ++ k)
					printf("%d ", l[i][k]);
				printf("%d\n", l[i][l[i].size() - 1]);
			}
		}
	}
	return 0;
}

