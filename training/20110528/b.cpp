#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

char a[1000010], d[1000010];
int l;

int main() {
	int ca = 0;
	while (true) {
		gets(a);
		l = strlen(a);
		if (a[0] == '0' && l == 1) break;
		reverse(a, a + l);
		for (int i = 0; i < l; ++ i) a[i] -= '0';
		d[0] = a[0]; d[l] = 0;
		for (int i = 1; i < l; ++ i) {
			a[i] -= d[i - 1];
			if (a[i] < 0) {
				a[i] += 10;
				-- a[i + 1];
			}
			d[i] = a[i];
		}
		for (int i = 0; i < l; ++ i)
			d[i] += '0';
		reverse(d, d + l);
		printf("%d. ", ++ ca);
		if (d[0] == '0') puts("IMPOSSIBLE");
		else puts(d);
	}
	return 0;
}

