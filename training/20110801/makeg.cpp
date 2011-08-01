#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <ctime>
#include <iostream>
using namespace std;

const int tests = 2;
const int n = 200000;
const int m = 200000;
const int p = 1203;

int main() {
	freopen("G.in", "w", stdout);
	printf("%d\n", tests);
	for (int i = 0; i < tests; ++ i) {
		printf("%d %d %d\n", n, m, p);
		for (int i = 0; i < m; ++ i)
			printf("%d %d %d\n", 1, n, rand() % 20 + 1);
	}
	return 0;
}
