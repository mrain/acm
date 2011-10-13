#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;

int main() {
	int tests = 1000;
	int n = 15;
	long long a = (1ll << 45ll) - 1ll;
	cout << tests << endl;
	for (int i = 0; i < tests; ++ i) {
		cout << n << endl;
		for (int j = 0; j < n; ++ j)
			cout << a << ' ';
		cout << endl;
	}
	return 0;
}
