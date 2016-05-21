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

int tests, t;
string str;

int main() {
	cin >> tests;
	for (int t = 1; t <= tests; ++ t) {
		cin >> str;
		int l = str.length();
		int result = 0;
		for (int i = 1; i < l; ++ i) {
			if (str[i] != str[i - 1])
				++ result;
		}
		result += (str[l - 1] == '+') ? 0 : 1;
		printf("Case #%d: %d\n", t, result);
	}
    return 0;
}
