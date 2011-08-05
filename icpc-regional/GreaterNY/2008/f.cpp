#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <iostream>
using namespace std;

char a[20000], b[20000];
int tests;

void init(char *a) {
	static char s[2000];
	scanf("%s", s);
	int n = 0, l = strlen(s);
	for (int i = 0; i < l; ) {
		s[i] = toupper(s[i]);
		if (isdigit(s[i]) || ((s[i] == '+' || s[i] == '-') && (!i || !isdigit(s[i - 1])) && isdigit(s[i + 1]))) {
			int p = n;
			if (s[i] == '-') a[n ++] = s[i ++];
			if (s[i] == '+') ++ i;
			while (isdigit(s[i])) a[n ++] = s[i ++];
			if (a[p] == '-') {
				bool flag = false;
				for (int i = p + 1; i < n; ++ i)
					if (a[i] != '0') {
						flag = true;
						break;
					}
				if (!flag) a[p] = '0';
			}
		} else {
			a[n ++] = char(s[i] / 100 + '0');
			a[n ++] = char((s[i] % 100) / 10 + '0');
			a[n ++] = char(s[i] % 10 + '0');
			++ i;
		}
		a[n ++] = ',';
	}
	a[n] = 0;
}

int cmp(char *a, char *b) {
	int i = 0, j = 0;
	while (1) {
		if (!a[i] && !b[i]) return 0;
		if (!a[i]) return -1;
		if (!b[i]) return 1;
		int p = i, q = j;
		int rev = 1;
		if (a[i] == '-' && b[i] == '-') rev *= -1;
		if (a[i] == '-' && b[i] != '-') return -1;
		if (a[i] != '-' && b[i] == '-') return 1;
		while (a[p] != ',') ++ p;
		while (b[q] != ',') ++ q;
		while (a[i] == '0') ++ i;
		while (b[j] == '0') ++ j;
		int la = p - i + 1, lb = q - j + 1;
		if (la < lb) return -1;
		if (la > lb) return 1;
		for (int k = 0; k < la; ++ k) {
			if (a[i + k] < b[j + k]) return -1;
			if (a[i + k] > b[j + k]) return 1;
		}
		i = p + 1; j = q + 1;
	}
	return 0;
}

int main() {
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		init(a);
		init(b);
//		cout << a << ' ' << b << endl;
		printf("%d %d\n", ++ ca, cmp(a, b));
	}
	return 0;
}
