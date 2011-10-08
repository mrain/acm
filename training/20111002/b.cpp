#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

char buf[2000];

bool isbracket(char p) {
	return p == '(' || p == ')' || p == '[' || p == ']';
}

bool valid(int l, int r) {
	while (l <= r && !isbracket(buf[l])) ++ l;
	while (r >= l && !isbracket(buf[r])) -- r;
/*	cout << l << ' ' << r << endl;
	for (int i = l; i <= r; ++ i) putchar(buf[i]);
	puts("");*/
	if (r < l) return true;
	if (buf[l] == ')' || buf[l] == ']') return false;
	int stack = 0;
	int cor = -1;
	if (buf[l] == '(') {
		for (int i = l; i <= r; ++ i) {
			if (buf[i] == '(') ++ stack;
			if (buf[i] == ')') -- stack;
			if (!stack) {
				cor = i;
				break;
			}
		}
	} else {
		for (int i = l; i <= r; ++ i) {
			if (buf[i] == '[') ++ stack;
			if (buf[i] == ']') -- stack;
			if (!stack) {
				cor = i;
				break;
			}
		}
	}
	if (cor == -1) return false;
	else return valid(cor + 1, r) && valid(l + 1, cor - 1);
}

int main() {
	while (gets(buf) && strcmp(buf, ".") != 0) {
		puts(valid(0, strlen(buf) - 1) ? "yes" : "no");
	}
	return 0;
}
