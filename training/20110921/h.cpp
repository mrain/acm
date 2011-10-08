#include <cstdio>
#include <iostream>
#include <cstdlib>
using namespace std;

int a = 6;

int main() {
	for (int i = 3; i < 10; ++ i) {
		printf("%d %d\n", i, a);
		a = a * a - 4 * a + 1;
	}
	return 0;
}
