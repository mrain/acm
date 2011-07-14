#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int a[5000], n;
bool vis[5000];

inline int abs(int a) {
	return a < 0 ? -a : a;
}

bool check() {
	for (int i = 1; i < n; ++ i) {
		int d = abs(a[i] - a[i - 1]);
		if (d < 1 || d >= n) return false;
		vis[d] = true;
	}
	for (int i = 1; i < n; ++ i)
		if (!vis[i]) return false;
	return true;
}

int main() {
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; ++ i)
			scanf("%d", a + i);
		memset(vis, 0, sizeof(vis));
		puts(check() ? "Jolly" : "Not jolly");
	}
	return 0;
}
