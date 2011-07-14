#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int n, m, cnt;
int a[1010], b[1010];
bool use[1010];

int main(int argc, char *argv[]) {
	cout.setf(ios::fixed);
	cout.precision(10);
	freopen(argv[1], "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++ i)
		scanf("%d%d", &a[i], &b[i]);
	freopen(argv[2], "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		int tmp;
		scanf("%d", &tmp);
		use[tmp] = true;
	}
	for (int i = 0; i < m; ++ i)
		if (use[a[i]] && use[b[i]]) ++ cnt;
	cout << cnt << '/' << n << ' ' << (double)cnt / n << endl;
	return 0;
}
