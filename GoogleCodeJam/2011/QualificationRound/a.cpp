#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int bpos, opos, btime, otime;
int tests, n, act;
char bot[10];

int main() {
	scanf("%d", &tests);
	int testcase = 0;
	while (tests --) {
		bpos = opos = 1;
		btime = otime = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; ++ i) {
			scanf("%s%d", bot, &act);
			if (bot[0] == 'O') {
				otime += abs(opos - act) + 1;
				otime = max(otime, btime + 1);
				opos = act;
			} else {
				btime += abs(bpos - act) + 1;
				btime = max(otime + 1, btime);
				bpos = act;
			}
		}
		printf("Case #%d: %d\n", ++ testcase, max(btime, otime));
	}
	return 0;
}

