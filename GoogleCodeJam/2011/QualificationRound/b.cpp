#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
#include <deque>
using namespace std;

int tests, C, D, n;
char c[255][255];
bool d[255][255];
char s[1000];
deque <char> list;

void invoke(char ch) {
	if (list.size() && c[list.back()][ch]) {
		char tmp = list.back();
		list.pop_back();
		list.push_back(c[tmp][ch]);
		return;
	}
	for (int i = 0; i < (int)list.size(); ++ i)
		if (d[list[i]][ch]) {
			list.clear();
			return;
		}
	list.push_back(ch);
}

int main() {
	scanf("%d", &tests);
	for (int testcase = 1; testcase <= tests; ++ testcase) {
		memset(c, 0, sizeof(c));
		memset(d, 0, sizeof(d));
		list.clear();
		scanf("%d", &C);
		for (int i = 0; i < C; ++ i) {
			scanf("%s", s);
			c[s[0]][s[1]] = c[s[1]][s[0]] = s[2];
		}
		scanf("%d", &D);
		for (int i = 0; i < D; ++ i) {
			scanf("%s", s);
			d[s[0]][s[1]] = d[s[1]][s[0]] = true;
		}
		scanf("%d%s", &n, s);
		for (int i = 0; i < n; ++ i) invoke(s[i]);
		printf("Case #%d: [", testcase);
		bool first = true;
		for (int i = 0; i < (int)list.size(); ++ i) {
			if (!first) printf(", ");
			first = false;
			putchar(list[i]);
		}
		puts("]");
	}
	return 0;
}

