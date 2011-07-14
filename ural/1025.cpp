#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int a[110], n, res;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%d", &a[i]);
	sort(a, a + n);
	res = 0;
	for (int i = 0; i <= n / 2; ++ i)
		res += (a[i] + 1) / 2;
	printf("%d\n", res);
	return 0;
}
