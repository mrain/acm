#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

const char *present[10] = {
	"oqz",
	"ij",
	"abc",
	"def",
	"gh",
	"kl",
	"mn",
	"prs",
	"tuv",
	"wxy"
};
int number[255];
int f[101], l[101], n, len[50010];
char str[200], word[50010][60], num[50010][60];
vector <int> ans;

bool check(int start, int pat) {
	for (int i = 0; i < len[pat]; ++ i)
		if (str[start + i] != num[pat][i]) return false;
	return true;
}

int main() {
	//init
	for (int i = 0; i < 10; ++ i) {
		int l = strlen(present[i]);
		for (int j = 0; j < l; ++ j)
			number[(int)present[i][j]] = i;
	}
	while (scanf("%s", str), strcmp(str, "-1") != 0) {
		scanf("%d", &n);
		memset(num, 0, sizeof(num));
		memset(f, 0x3F, sizeof(f));
		memset(l, 0, sizeof(l));
		for (int i = 0; i < n; ++ i) {
			scanf("%s", word[i]);
			len[i] = strlen(word[i]);
			for (int j = 0; j < len[i]; ++ j)
				num[i][j] = number[(int)word[i][j]] + '0';
		}
		int m = strlen(str);
		for (int i = 0; i < m; ++ i)
			for (int j = 0; j < n; ++ j)
				if (len[j] <= i + 1 && check(i - len[j] + 1, j)) {
					if (i - len[j] == -1) {
						f[i] = 1;
						l[i] = j;
					} else if (f[i] > f[i - len[j]] + 1) {
						f[i] = f[i - len[j]] + 1;
						l[i] = j;
					}
				}
		if (f[m - 1] == 0x3F3F3F3F) puts("No solution.");
		else {
			int now = m - 1;
			ans.clear();
			while (now > 0) {
				ans.push_back(l[now]);
				now -= len[l[now]];
			}
			for (int i = ans.size() - 1; i >= 0; -- i) {
				printf("%s", word[ans[i]]);
				if (i) putchar(' ');
			}
		}
	}
	return 0;
}
