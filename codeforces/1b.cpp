#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

int r, c, tests, l;
char buf[3000];

void put1(int a, int b) {
	printf("R%dC%d\n", a, b);
}

void put2(int a, int b) {
	string tmp;
	while (a) {
		tmp += char((a - 1) % 26) + 'A';
		a = (a - 1) / 26;
	}
	reverse(tmp.begin(), tmp.end());
	printf("%s%d\n", tmp.c_str(), b);
}

bool check() {
	int j = 0;
	while (!isdigit(buf[j])) ++ j;
	while (j < l && isdigit(buf[j])) ++ j;
	return isupper(buf[j]);
}

int main() {
	scanf("%d", &tests);
	while (tests --) {
		scanf("%s", buf);
		r = c = 0;
		l = strlen(buf);
		if (check()) {
			int j = 1;
			while (isdigit(buf[j])) {
				r = r * 10 + (buf[j] - '0');
				++ j;
			}
			++ j;
			while (isdigit(buf[j])) {
				c = c * 10 + (buf[j] - '0');
				++ j;
			}
			put2(c, r);
		} else {
			int j = 0;
			while (isupper(buf[j])) {
				c = c * 26 + (buf[j] - 'A' + 1);
				++ j;
			}
			while (isdigit(buf[j])) {
				r = r * 10 + (buf[j] - '0');
				++ j;
			}
			put1(r, c);
		}
	}
	return 0;
}

