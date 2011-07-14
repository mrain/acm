#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <cmath>
#include <cctype>
using namespace std;

const int maxsize = 20000;
int n;
int reach[2 * maxsize + 10], a[10000];
double b[10000];
double sum;

void putans(int now, bool mark) {
	if (now == 0 || reach[now] <= 0) return;
	putans(now - a[reach[now] - 1], false);
	if (mark) printf("%d\n", reach[now]);
	else printf("%d ", reach[now]);
}

int main() {
	while (1) {
		scanf("%d", &n); sum = 0;
		if (!n) break;
		memset(reach, 0xFF, sizeof(reach));
		for (int i = 0; i < n; ++ i) {
			scanf("%lf", &b[i]);
			sum += b[i];
		}
		for (int i = 0; i < n; ++ i) a[i] = b[i] * maxsize / sum;
		reach[0] = 0;
		for (int i = 0; i < n; ++ i)
			for (int j = maxsize; j >= a[i]; -- j)
				if (reach[j - a[i]] >= 0 && reach[j] < 0)
					reach[j] = i + 1;
		for (int i = maxsize / 2; i >= 0; -- i)
			if (reach[i] >= 0) {
				putans(i, true);
				break;
			}
	}
	return 0;
}

