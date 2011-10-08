#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cctype>
#include <iostream>
using namespace std;

#define PB push_back
#define MP make_pair
#define A first
#define B second

typedef pair<int, int> PII;

vector<int> e[100000], ser;
char s[1100000];
vector<PII> ans, name;
int n, now, father[1100000], STACK[1100000], top;

void pop() {
	int tmp = STACK[top --];
	if (top) ans.PB(MP(tmp, STACK[top]));
}
void push(int t) {
	STACK[++ top] = t;
	ans.PB(MP(STACK[top - 1], STACK[top]));
}

void work1() {
	STACK[top = 1] = 1;
	int cur = 1;
	for (int i = 0; i < ser.size(); ++ i) {
		if (ser[i] == 2) pop();
		else {
			++ cur;
			if (ser[i] == 0) pop();
			push(cur);
		}
	}
}

void work() {
	scanf("%s", s);
	
	name.clear(), ser.clear();
	for (int i = 0; s[i]; ++i) {
		if (s[i] == ',') {
			ser.PB(0); continue;
		}
		if (s[i] == '(') {
			ser.PB(1); continue;
		}
		if (s[i] == ')') {
			ser.PB(2); continue;
		}
	
		int st = i;
		for (; s[i] && islower(s[i]); ++i);
		//cout << st << ' ' << i << endl;
		name.PB(MP(st, i)), i--;
	}
	
	ans.clear(), now = 0;
	//dfs(1, 0);
	work1();
	
	n = name.size();
	printf("%d\n", n);
	for (int i = 0; i < n; ++i) {
		for (int j = name[i].A; j < name[i].B; ++j) putchar(s[j]);
		puts("");
	}
	for (int i = 0; i < ans.size(); ++i) printf("%d %d\n", ans[i].A, ans[i].B);
	puts("");
}

int main() {
	int T; scanf("%d", &T);
	
	while (T--) work();

	return 0;
}
