#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

int tests, a[3];
char buf[300];

int main() {
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		scanf("%s", buf);
		a[0] = (buf[0] - '0') * 10 + buf[1] - '0';
		a[1] = (buf[3] - '0') * 10 + buf[4] - '0';
		a[2] = (buf[6] - '0') * 10 + buf[7] - '0';
		printf("%d ", ++ ca);
		for (int i = 5; i >= 0; -- i)
			for (int j = 0; j < 3; ++ j) {
				if (a[j] & (1 << i)) putchar('1');
				else putchar('0');
			}
		putchar(' ');
		for (int j = 0; j < 3; ++ j)
			for (int i = 5; i >= 0; -- i) {
				if (a[j] & (1 << i)) putchar('1');
				else putchar('0');
			}
		puts("");
	}
	return 0;
}
