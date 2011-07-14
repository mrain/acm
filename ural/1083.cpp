#include <cstdio>
#include <cstring>

int n, res, k;
char str[30];

int main() {
	scanf("%d%s", &n, str);
	res = 1;
	k = strlen(str);
	for (int i = n; i > 0; i -= k) res *= i;
	printf("%d\n", res);
}
