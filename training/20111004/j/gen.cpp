#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <iostream>
using namespace std;

int bound = 10000000;
int tests, h, w, n, m;

int main() {
	srand(time(0));
	freopen("input.txt", "w", stdout);
	for (int t = 0; t < 10; ++ t) {
		h = rand() % (bound / 2) + bound / 2 + 1;
		w = rand() % (bound / 2) + bound / 2 + 1;
		n = 50000;
		//m = rand() % 500 + 500 + 1;
		m = 1;
		cout << w << ' ' << h << ' ' << n << ' ' << m << endl;
		for (int i = 0; i < n; ++ i) {
			int x1 = rand() % w + 1, y1 = rand() % h + 1;
			int x2 = rand() % (w - x1 + 1) + x1;
			int y2 = rand() % (h - y1 + 1) + y1;
			cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
		}
	}
	return 0;
}

