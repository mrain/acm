#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int vis[1000][1000];
int win[1000][1000];
int ans[1000];

bool dfs(int x, int y) {
	if (vis[x][y]) return win[x][y];
	vis[x][y] = true; win[x][y] = false;
	if (x == 0) return false;
	for (int i = 1; i * x <= y; ++ i) {
		int a = x, b = y - i * x;
		if (b < a) swap(a, b);
		if (!dfs(a, b)) {
			win[x][y] = true;
			break;
		}
	}
	return win[x][y];
}

int main() {
	for (int n = 1; n <= 30; ++ n) {
		int last=0;
		for (int i = 1; i <= n; ++ i) {
			for (int j = i + 1; j <= n; ++ j)
				if ( !dfs(i, j) ) {
					ans[n] += i + j;
				}
			//puts("");
		}
		//printf("%d,", ans[n]);
	}
	for (int i = 2; i <= 30; ++ i)
		printf("%d,", ans[i] - ans[i - 1]);
	/*
	long long sum = 0;
	double r = (1. + sqrt(5.)) / 2.;
	for (int n = 1; n < 50; ++ n) {
		sum += (long long)(r * n + 1e-9)+1;
		printf("%d %lld\n", n, sum);
	}*/
	return 0;
}

