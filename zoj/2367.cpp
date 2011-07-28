#include <cstdio>
#include <cctype>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <cstring>
#include <map>
#include <sstream>
using namespace std;

int tests;
string op, a, b, buf;
int pp[10000], stack[10000], top;
map<string, string> p;

long long power(long long a, long long b) {
	long long ret = 1;
	while (b) {
		if (b & 1) ret *= a;
		a *= a;
		b >>= 1;
	}
	return ret;
}

string itoa(long long p) {
	string ret = "";
	bool flag = (p < 0);
	if (flag) p *= -1;
	while (p) {
		ret += char(p % 10 + '0');
		p /= 10;
	}
	if (flag) ret += '-';
	reverse(ret.begin(), ret.end());
	return ret;
}

long long atoi(const string &a) {
	if (!isdigit(a[0]) && a[0] != '-') return 0;
	long long ret = 0, start = (a[0] == '-') ? 1 : 0;
	for (int i = start; i < (int)a.length(); ++ i)
		ret = ret * 10 + a[i] - '0';
	return (a[0] == '-') ? -ret : ret;
}

string get(const string &a) {
	if (!p.count(a)) return a;
	else return p[a] = get(p[a]);
}

bool isoperator(char c) {
	return c == '+' || c == '-' || c == '^' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')';
}

long long eval(int l, int r) {
	while (pp[l] == r) ++ l, -- r;
//	cout << l << ' ' << r << ' ' << a.substr(l, r - l + 1) << endl;
	int stack = 0;
	for (int i = r; i >= l; -- i) {
		if (a[i] == '(') ++ stack;
		if (a[i] == ')') -- stack;
		if (!stack && (a[i] == '+' || a[i] == '-') && i > l && !(isoperator(a[i - 1]) && a[i - 1] != ')')) {
			long long p = eval(l, i - 1), q = eval(i + 1, r);
			if (a[i] == '+') p += q;
			else p -= q;
			return p;
		}
	}
	stack = 0;
	for (int i = r; i >= l; -- i) {
		if (a[i] == '(') ++ stack;
		if (a[i] == ')') -- stack;
		if (!stack && (a[i] == '*' || a[i] == '/' || a[i] == '%')) {
			long long p = eval(l, i - 1), q = eval(i + 1, r);
			if (a[i] == '*') p *= q;
			else if (a[i] == '/') p /= q;
			else {
				long long tmp = abs(p) % abs(q);
				if (p < 0 && q > 0) p = -tmp;
				else if (p > 0 && q < 0) p = -tmp;
				else p = tmp;
			}
			return p;
		}
	}
	stack = 0;
	for (int i = l; i <= r; ++ i) {
		if (a[i] == '(') ++ stack;
		if (a[i] == ')') -- stack;
		if (!stack && a[i] == '^') {
			long long p = eval(l, i - 1);
			if (p != 0 && p != 1) {
				long long q = eval(i + 1, r);
				p = power(p, q);
			}
			return p;
		}
	}
	if (a[l] == '-') return -eval(l + 1, r);
	if (a[l] == '+') return eval(l + 1, r);
	string tmp = a.substr(l, r - l + 1);
	return atoi(get(tmp));
}

int main() {
	cin >> tests;
	getline(cin, buf);
	getline(cin, buf);
	while (tests --) {
		p.clear();
		while (getline(cin, buf) && buf.length() > 0u) {
			for (int i = 0; i < (int)buf.length(); ++ i)
				buf[i] = tolower(buf[i]);
			istringstream is(buf);
			is >> op;
			if (op[0] == 'd') {
				is >> a >> b;
				if (!p.count(a) && get(b) != a) p[a] = b;
			} else {
				b = buf.substr(5);
				a = "";
				for (int i = 0; i < (int)b.length(); ++ i)
					if (b[i] != ' ') a += b[i];
				memset(pp, -1, sizeof(pp));
				top = 0;
				for (int i = 0; i < (int)a.length(); ++ i) {
					if (a[i] == '(') stack[++ top] = i;
					if (a[i] == ')') {
						pp[stack[top]] = i;
						pp[i] = stack[top --];
					}
				}
				cout << eval(0, a.length() - 1) << endl;
			}
		}
		if (tests) cout << endl;
	}
	return 0;
}

