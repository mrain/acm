#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

char a[1000010];
int n, ans;

int main() {
	memset(a, 0, sizeof(a));
	scanf("%s", a);
	n = strlen(a);
	reverse(a, a + n);
	for (int i = 0; a[i + 1]; ++ i) {
		if (a[i] == '0') ++ ans;
		else {
			int j = i; ans += 2;
			while (a[j + 1] == '1') ++ j, ++ ans;
			i = j; a[j + 1] = '1';
		}
	}
	printf("%d\n", ans);
	return 0;
}
