#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <string>
using namespace std;

const int n = 10000, c = 20000;
const int test = 1;

int main() {
	srand(time(0));
	freopen("c.in", "w", stdout);
	for (int tt = 0; tt < test; ++ tt) {
		cout << n << ' ' << c << endl;
		for (int i = 0; i < n; ++ i)
			cout << 2 << ' ';
		cout << endl;
		for (int i = 0; i < c; ++ i) {
			int p = (rand() % (n - 1)) + 1;
			int r = rand() % (4 * 90);
			cout << p << ' ' << r << endl;
		}
	}
	return 0;
}

