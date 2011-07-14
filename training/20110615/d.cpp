#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const string mm[13] = {
	"",
	"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
	"JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

inline string toString(int a) {
	string ret = "";
	ret.push_back((char)(a / 10 + '0'));
	ret.push_back((char)(a % 10 + '0'));
	return ret;
}

struct date {
	int day, month, year;
	date(int d = 0, int m = 0, int y = 0)
		:day(d), month(m), year(y) {}
	string toString() {
		return ::toString(day) + mm[month] + ::toString(year);
	}
	bool avai() {
		return day > 0 && day <= 31 && month > 0 && month <= 12;
	}
	bool operator <(const date &t) {
		return year < t.year || (year == t.year && (month < t.month || (month == t.month && day < t.day)));
	}
};

string s;
date curdate(9, 11, 3);
int n, ca;

inline void bad() {
	printf("<Kalii Index=%d>BAD DATA</Kalii>\n", ++ ca);
}

void make() {
	double rate = 0;
	date start, end;
	bool f1 = false, f2 = false, f3 = false;
	for (int i = 0; i < n; ++ i) {
		if (s[i] == '.') f1 = true;
		if (s[i] == '%') f2 = true;
		if (s[i] == '/') f3 = true;
	}
	if (f1 || (f2 && f3) || !(f2 || f3)) {
		bad();
		return;
	}
	int cur = 0;
	if (f2) {
		for (int i = 0; i < n; ++ i)
			if (s[i] == '%') {
				cur = i + 1;
				break;
			} else rate = rate * 10 + (s[i] - '0');
	} else {
		int i;
		for (i = 0; i < n; ++ i)
			if (s[i + 1] == '/') break;
			else rate = rate * 10 + (s[i] - '0');
		if (i + 2 >= n) {
			bad();
			return;
		}
		if ((s[i + 2] != '2' && s[i + 2] != '4' && s[i + 2] != '8') || s[i] >= s[i + 2]) {
			bad();
			return;
		}
		rate += (double)(s[i] - '0') / (double) (s[i + 2] - '0');
		cur = i + 3;
	}
	for (int i = cur; i < n; ++ i)
		if (!isdigit(s[i]) && s[i] != '-' && s[i] != ' ') {
			bad();
			return;
		}
	while (s[cur] == ' ') ++ cur;
	if (!isdigit(s[cur])) {
		bad();
		return;
	}
	end.day = 15;
	end.month = s[cur ++] - '0';
	if (!(end.month * 10 + s[cur] - '0' > 12 || s[cur] == '-'))
		end.month = end.month * 10 + s[cur ++] - '0';
	if (s[cur] == '-') ++ cur;
	end.year = s[cur ++] - '0';
	if (isdigit(s[cur]))
		end.year = end.year * 10 + s[cur ++] - '0';
	while (s[cur] == ' ') ++ cur;
	if (!isdigit(s[cur])) {
		bad();
		return;
	}
	start.month = s[cur ++] - '0';
	if (!(start.month * 10 + s[cur] - '0' > 12 || s[cur] == '-'))
		start.month = start.month * 10 + s[cur ++] - '0';
	if (s[cur] == '-') ++ cur;
	start.day = s[cur ++] - '0';
	if (isdigit(s[cur]) && (start.day * 10 + s[cur] - '0' <= 31))
		start.day = start.day * 10 + s[cur ++] - '0';
	while (start < curdate)
		++ start.year;
	if (end < start || !end.avai() || !start.avai()) {
		bad();
		return;
	}
	printf("<Kalii Index=%d>\n", ++ ca);
	printf("    <startdate>%s</startdate>\n", start.toString().c_str());
	printf("    <rate>%.3f</rate>\n", rate);
	printf("    <enddate>%s</enddate>\n", end.toString().c_str());
	printf("</Kalii>\n");
}

int main() {
	ca = 0;
	while (getline(cin, s)) {
		n = (int)s.length();
//		if (!n) continue;
		make();
	}
	return 0;
}

