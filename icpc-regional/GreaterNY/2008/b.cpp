#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

char buf[1010];
char a[300];
int tests, n;

int main() {
	scanf("%d ", &tests);
	int ca = 0;
	while (tests --) {
		gets(buf); gets(a);
		n = strlen(buf);
		printf("%d ", ++ ca);
		for (int i = 0; i < n; ++ i) {
			if (isupper(buf[i])) buf[i] = a[(int)(buf[i] - 'A')];
			putchar(buf[i]);
		}
		puts("");
	}
	return 0;
}
