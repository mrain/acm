#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

int main() {
	srand(time(0));
	freopen("f.in", "w", stdout);
	for (int t = 0; t < 5; ++ t) {
		for (int i = 0; i < 1000; ++ i)
			printf("%d %d\n", rand() % 100000, rand() % 100000);
		puts("----");
	}
	puts("----");
	return 0;
}

