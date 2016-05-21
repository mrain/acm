#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

int T, n;
long long m;
string s,t;



void multi(char &a, int &sgn, char b) {
	// sgn a * b
	if (a == '1') a = b;
	else if (a == 'i') {
		if (b == 'i') sgn = -sgn, a = '1';
		else if (b == 'j') a = 'k';
		else if (b == 'k') sgn = -sgn, a = 'j';
	} else if (a == 'j') {
		if (b == 'i') sgn = -sgn, a = 'k';
		else if (b == 'j') sgn = -sgn, a = '1';
		else if (b == 'k') a = 'i';
	} else if (a == 'k') {
		if (b == 'i') a = 'j';
		else if (b == 'j') sgn = -sgn, a = 'i';
		else if (b == 'k') sgn = -sgn, a = '1';
	}
}

bool check(string s) {
	char res = '1';
	int	sgn = 1, cur = 0, l = s.length();

	for (; cur < l; ++ cur) {
		if (res == 'i' && sgn == 1) 
			break;
		multi(res, sgn, s[cur]);
	}
	if (cur == l) return false;

	res = '1'; sgn = 1;
	for (; cur < l; ++ cur) {
		if (res == 'j' && sgn == 1) 
			break;
		multi(res, sgn, s[cur]);
	}
	if (cur == l) return false;

	res = '1'; sgn = 1;
	for (; cur < l; ++ cur) {
		multi(res, sgn, s[cur]);
	}
	return (res == 'k' && sgn == 1);
}

int main() {
	cin >> T;
	for (int test = 0; test < T; ++ test) {
		cin >> n >> m >> t;
		m = min(m, m % 4 + 16);
		s = "";
		for (int i = 0; i < m; ++ i)
			s += t;
		printf("Case #%d: %s\n", test + 1, check(s) ? "YES" : "NO");
	}
    return 0;
}
