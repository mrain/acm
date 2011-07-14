#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;
int l, m;
PII a[10000];

int main() {
	while (1) {
		scanf("%d%d", &l, &m);
		if (l == 0 && m == 0) break;
		for (int i = 0; i < m; ++ i)
			scanf("%d%d", &a[i].first, &a[i].second);
		sort(a, a + m);
		l -= a[0].second - a[0].first;
		for (int i = 1; i < m; ++ i) {
			l -= a[i].second - a[i].first + 1;
			if (a[i].first == a[i - 1].second) ++ l;
		}
		printf("%d\n", l);
	}
	return 0;
}

