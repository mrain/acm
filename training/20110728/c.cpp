#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

int P, Q, R;
string buf;

int eval(int l, int r) {
	if (buf[l] == '-') return 2 - eval(l + 1, r);
	if (buf[l] == 'P') return P;
	if (buf[l] == 'R') return R;
	if (buf[l] == 'Q') return Q;
	if (isdigit(buf[l])) return buf[l] - '0';
	int stack = 0, split = l;
	for (int i = l + 1; i < r; ++ i) {
		if (buf[i] == '(') ++ stack;
		if (buf[i] == ')') -- stack;
		if (!stack && (buf[i] == '+' || buf[i] == '*')) {
			split = i;
			break;
		}
	}
	int a = eval(l + 1, split - 1), b = eval(split + 1, r - 1);
	if (buf[split] == '*') return min(a, b);
	else return max(a, b);
}

int main() {
	while (getline(cin, buf) && buf[0] != '.') {
		int l = buf.length(),ans = 0;
		for (P = 0; P <= 2; ++ P)
			for (Q = 0; Q <= 2; ++ Q)
				for (R = 0; R <= 2; ++ R)
					if (eval(0, l - 1) == 2)
						++ ans;
		cout << ans << endl;
	}
	return 0;
}
