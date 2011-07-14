#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <cmath>
#include <cctype>
using namespace std;

int tests, n;
char s[10000];
int cnt[255];
bool used[10000];

inline bool check() {
	bool flag = false;
	for (int i = 'a'; i <= 'z'; ++ i)
		if ((cnt[i] & 1) == 1) {
			if (flag) return false;
			flag = true;
		}
	return true;
}

inline int abs(int a) { return a < 0 ? -a : a; }

int work() {
	memset(used, 0, sizeof(used));
	int ret = 0;
	if ((n & 1) == 1) {
		for (int i = 0; i < n; ++ i)
			if ((cnt[(int)s[i]] & 1) == 1) {
				ret += abs(n / 2 - i);
				used[i] = true;
			}
	}
	for (int i = 0; i < n; ++ i)
		if (!used[i]) {
			int j = n - 1, cnt = 0;
			while (used[j] || s[i] != s[j]) {
				if (!used[j]) ++ cnt;
				-- j;
			}
			ret += cnt;
			used[j] = used[i] = true;
		}
	return ret;
}

int main() {
	scanf("%d", &tests);
	while (tests --) {
		memset(cnt, 0, sizeof(cnt));
		scanf("%s", s);
		n = strlen(s);
		for (int i = 0; i < n; ++ i)
			++ cnt[(int)s[i]];
		if (!check()) puts("Impossible");
		else {
			printf("%d\n", work());
		}
	}
	return 0;
}

