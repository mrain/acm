#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
#define two(x) (1<<(x))
#define lowbit(x) ((x)&(-(x)))

typedef pair<int, int> PII;
map <PII, int> f;
int n, highbit[two(20)], l2[two(20)];

int dfs(int a, int b) {
	if (b == 0) return f[make_pair(a, b)];
	if (f.find(make_pair(a, b)) != f.end()) return f[make_pair(a, b)];
	else return f[make_pair(a, b)] = dfs(a, b - highbit[b]) + dfs(a + highbit[b], b - highbit[b]);
}

int main() {
	for (int i = 1; i < two(20); ++ i) {
		highbit[i] = (lowbit(i) == i) ? i : highbit[i - 1];
		l2[i] = l2[i - 1] + (lowbit(i) == i);
	}
	while (scanf("%d", &n) == 1 && n != -1) {
		f.clear();
		int maxlen = 0;
		for (int i = 0; i < n; ++ i) {
			int c, v;
			scanf("%d%d", &c, &v);
			f[make_pair(c, 0)] += v;
			maxlen = max(maxlen, l2[c]);
		}
		maxlen = 20;
		int ans = 0;
		for (int i = 0; i < two(maxlen); ++ i)
			ans = dfs(0, i);
		cout << ans << endl;
	}
	return 0;
}
