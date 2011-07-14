#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> PII;
char exp[500], dig[500], buf[500];
int tests, n, m;
long long pow[100];
vector <PII> l;

void deal(char *exp, int l, int r) {
	int eip = l;
	while (eip < r) {
		if (exp[eip] != '(') {
			++ eip;
			continue;
		}
		int stack = 1, pair;
		for (pair = eip + 1; stack; ++ pair) {
			if (exp[pair] == '(') ++ stack;
			if (exp[pair] == ')') -- stack;
		}
		deal(exp, eip + 1, pair - 2);
		if (eip && exp[eip - 1] == '-') {
			for (int i = eip; i < pair; ++ i)
				if (exp[i] == '+') exp[i] = '-';
				else if (exp[i] == '-') exp[i] = '+';
		}
		exp[eip] = exp[pair - 1] = '?';
		eip = pair;
	}
}

inline bool cmp(const PII &a, const PII &b) {
	if (a.first == b.first) return a.second > b.second;
	else return a.first > b.first;
}

void pre() {
	deal(exp, 0, n - 1);
	l.clear();
	for (int i = 0; i < n;) {
		if (exp[i] != '#') {
			++ i;
			continue;
		}
		int j = i + 1, len = 1, k = 1;
		while (exp[j] == '#') ++ j, ++ len;
		int p = i - 1;
		while (p >= 0 && exp[p] == '?') -- p;
		if (p >= 0 && exp[p] == '-') k = -1;
		for (int p = i; p < j; ++ p)
			l.push_back(make_pair((len - p + i) * k, p));
		i = j;
	}
	sort(l.begin(), l.end(), cmp);
}

int main() {
	scanf("%d", &tests);
	pow[0] = 1;
	for (int i = 1; i <= 15; ++ i)
		pow[i] = pow[i - 1] * 10;
	int ca = 0;
	while (tests --) {
		scanf("%s", exp);
		scanf("%s", dig);
		n = strlen(exp), m = strlen(dig);
		strcpy(buf, exp);
		sort(dig, dig + m);
		reverse(dig, dig + m);
		pre();
		cout << "Case " << ++ ca << ":" << endl;
		long long res = 0;
		for (int i = 0; i < (int)l.size(); ++ i) {
			buf[l[i].second] = dig[i];
			if (l[i].first > 0) res += pow[l[i].first - 1] * (dig[i] - '0');
			else res -= pow[-l[i].first - 1] * (dig[i] - '0');
		}
		cout << buf << endl << res << endl;
	}
	return 0;
}

