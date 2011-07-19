#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int tests;
int n;

int main() {
	scanf("%d", &tests);
	while (tests --) {
		scanf("%d", &n);
		if (n <= 2) printf("0\n");
		else printf("%d\n", n - 2);
	}
	return 0;
}
