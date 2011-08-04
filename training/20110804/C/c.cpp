#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int n = 5, m = 4, k = 3;
int a[100], cnt[100];
int res[50][50];
int tmp;

void dfs(int d) {
	if (d == k) {
		int A = 0, B = 0;
		for (int i = 0; i < m; ++ i)
			if (cnt[i] & 1) ++ A;
		for (int i = m; i < n; ++ i)
			if (cnt[i] & 1) ++ B;
		++ res[A][B];
		if (cnt[0] == 0) ++ tmp;
		return;
	}
	for (int i = 0; i < n; ++ i) {
		a[d] = i; cnt[i] ++;
		dfs(d + 1);
		cnt[i] --;
	}
}

int main() {
	dfs(0);
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < n; ++ j)
			printf("%d %d %d\n", i, j, res[i][j]);
	cout << tmp << endl;
	return 0;
}
