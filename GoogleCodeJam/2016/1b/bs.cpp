#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

int tests;
string a, b;

void searcha(int i) {
	if (a[i] == '?') {
		for (int c = '0'; c <= '9'; ++ c)
			a[i] = c;
	}
}

int main() {
	cin >> tests;
	for (int cases = 1; cases <= tests; ++ cases) {
		cin >> a >> b;
		cout << "Case #" << cases << ": " << a << " " << b << endl;
	}
    return 0;
}
