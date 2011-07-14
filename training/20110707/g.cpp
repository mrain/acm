#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

int n, c, p, ans[10000];
bool used[10000];

int main() {
	while (scanf("%d", &n), n) {
		bool flag = true;
		memset(used,0, sizeof(used));
		for (int i = 0; i < n; ++ i) {
			scanf("%d%d", &c, &p);
			if (i + p < 0 || i + p >= n || used[i + p]) {
				flag = false;
				continue;
			}
			used[i + p] = true;
			ans[i + p] = c;
		}
		if (!flag) puts("-1");
		else {
			for (int i = 0; i < n; ++ i) {
				if (i) putchar(' ');
				printf("%d", ans[i]);
			}
			puts("");
		}
	}
	return 0;
}
