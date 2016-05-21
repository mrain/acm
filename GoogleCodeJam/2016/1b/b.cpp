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

string empty;
int tests;
string a, b;
string s1maxa, s1maxb, s1mina, s1minb, s2maxa, s2maxb, s2mina, s2minb;

long long turn(string a) {
	long long s = 0;
	for (int i = 0; i < a.length(); ++ i) {
		s = s * 10ll + a[i] - '0';
	}
	return s;
}

void update(string &a, string &b, char ca, char cb, string mina, string minb, string maxa, string maxb) {
	if (ca == '?') {
		if (cb == '?') {
			mina = "0" + mina;
			minb = "0" + minb;
			maxa = "1" + maxa;
			maxb = "0" + maxb;
			long long s1a = turn(mina), s1b = turn(minb);
			long long s2a = turn(maxa), s2b = turn(maxb);
			//cout << s1a << ' ' << s1b << ' ' << s2a << ' ' << s2b << endl;
			if (abs(s1a - s1b) < abs(s2a - s2b)) {
				a = mina; b = minb;
			} else if (abs(s1a - s1b) == abs(s2a - s2b) && s1b < s2b) {
				a = mina; b = minb;
			} else {
				a = maxa; b = maxb;
			}
		} else {
			//
			if (cb == '9') {
				a = empty + cb + mina;
				b = empty + cb + minb;
				return;
			}
			mina = empty + cb + mina;
			minb = empty + cb + minb;
			maxa = empty + char(cb + 1) + maxa;
			maxb = empty + cb + maxb;
			long long s1a = turn(mina), s1b = turn(minb);
			long long s2a = turn(maxa), s2b = turn(maxb);
			if (abs(s1a - s1b) < abs(s2a - s2b)) {
				a = mina; b = minb;
			} else if (abs(s1a - s1b) == abs(s2a - s2b) && s1b < s2b) {
				a = mina; b = minb;
			} else {
				a = maxa; b = maxb;
			}
		}
	} else if (cb == '?') {
		//
		if (ca == '0') {
			a = empty + ca + mina;
			b = empty + ca + minb;
			return;
		}
		mina = empty + ca + mina;
		minb = empty + ca + minb;
		maxa = empty + ca + maxa;
		maxb = empty + char(ca - 1) + maxb;
		long long s1a = turn(mina), s1b = turn(minb);
		long long s2a = turn(maxa), s2b = turn(maxb);
		if (abs(s1a - s1b) < abs(s2a - s2b)) {
			a = mina; b = minb;
		} else if (abs(s1a - s1b) == abs(s2a - s2b) && s1b < s2b) {
			a = mina; b = minb;
		} else {
			a = maxa; b = maxb;
		}
	} else {
		mina = empty + ca + mina;
		minb = empty + cb + minb;
		maxa = empty + ca + maxa;
		maxb = empty + cb + maxb;
		long long s1a = turn(mina), s1b = turn(minb);
		long long s2a = turn(maxa), s2b = turn(maxb);
		if (abs(s1a - s1b) < abs(s2a - s2b)) {
			a = mina; b = minb;
		} else if (abs(s1a - s1b) == abs(s2a - s2b) && s1b < s2b) {
			a = mina; b = minb;
		} else {
			a = maxa; b = maxb;
		}
	}
}

void updatemax(string &a, string &b, char ca, char cb, string maxa, string maxb) {
	//cout << ca << ' ' << cb << endl;
	if (ca == '?') a = "9" + maxa;
	else a = empty + ca + maxa;
	if (cb == '?') b = "0" + maxb;
	else b = empty + cb + maxb;
}

int main() {
	empty = "";
	cin >> tests;
	for (int cases = 1; cases <= tests; ++ cases) {
		cin >> a >> b;
		s1maxa = s1maxb = s2maxa = s2maxb = s1mina = s1minb = s2mina = s2minb = "";
		int mark = 0; // UNDECIDED
		for (int i = a.length() - 1; i >= 0; -- i) {
			update(s1mina, s1minb, a[i], b[i], s1mina, s1minb, s2maxa, s2maxb);
			update(s2minb, s2mina, b[i], a[i], s2minb, s2mina, s1maxb, s1maxa);
			updatemax(s1maxa, s1maxb, a[i], b[i], s1maxa, s1maxb);
			updatemax(s2maxb, s2maxa, b[i], a[i], s2maxb, s2maxa);

			/*cerr << "s1min :" << s1mina << " " << s1minb << endl;
			cerr << "s1max :" << s1maxa << " " << s1maxb << endl;
			cerr << "s2min :" << s2mina << " " << s2minb << endl;
			cerr << "s2max :" << s2maxa << " " << s2maxb << endl;*/
			/*if (a[i] == '?') {
				if (b[i] == '?') {
				} else {
				}
			} else {
				if (b[i] == '?') {
				} else {
					s1maxa = "" + a[i] + s1maxa;
					s1mina = "" + a[i] + s1mina;
					s2maxa = "" + a[i] + s2maxa;
					s2mina = "" + a[i] + s2mina;
					s1minb = "" + b[i] + s1minb;
					s1maxb = "" + b[i] + s1maxb;
					s2minb = "" + b[i] + s2minb;
					s2maxb = "" + b[i] + s2maxb;
				}
			}*/
		}
		long long s1a = turn(s1mina), s1b = turn(s1minb);
		long long s2a = turn(s2mina), s2b = turn(s2minb);
		if (abs(s1a - s1b) < abs(s2a - s2b) || (abs(s1a - s1b) == abs(s2a - s2b) && s1b < s2b)) {
			a = s1mina; b = s1minb;
		} else {
			a = s2mina; b = s2minb;
		}
		cout << "Case #" << cases << ": " << a << " " << b << endl;
	}
    return 0;
}
