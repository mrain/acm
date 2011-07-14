#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>
using namespace std;

int w, l, n;
vector <int> ans, tmp;
string buff, a[400], sb[400], s[200000];
int cur, asc[400], eoln;
map <string, int> id;
vector <int> b[400];

inline int get(const string &s) {
	if (id.count(s)) return id[s];
	id.insert(make_pair(s, id.size()));
	return id.size() - 1;
}

void append(vector <int> &l, const vector <int> &t) {
	for (int i = 0; i < (int)t.size(); ++ i)
		l.push_back(t[i]);
}

void append(vector <int> &l, const vector <string> &t) {
	for (int i = 0; i < (int)t.size(); ++ i)
		l.push_back(get(t[i]));
}

void append(vector <int> &l, const string &s) {
	int pre = 0;
	for (int i = 0; i < (int)s.length(); ++ i)
		if (s[i] == ' ') {
			if (pre != i) l.push_back(get(s.substr(pre, i - pre)));
			pre = i + 1;
		}
	if (pre != (int)s.length())
		l.push_back(get(s.substr(pre, (int)s.length() - pre)));
}

inline int cnt(const string &s) {
	int ret = 0;
	for (int i = 0; i < (int)s.length(); ++ i)
		ret += s[i] != ' ' ? 1 : 0;
	return ret;
}

void init() {
	getline(cin, buff);
	sscanf(buff.c_str(), "%d%d%d", &w, &l, &n);
	for (int i = 0; i < n; ++ i) {
		getline(cin, buff);
		int j = 0;
		while (buff[j] != ' ') ++ j;
		a[i] = buff.substr(0, j);
		sb[i] = buff.substr(j + 1, (int)buff.length() - j - 1);
		asc[i] = cnt(sb[i]) - cnt(a[i]);
		get(a[i]);
	}
	for (int i = 0; i < n; ++ i)
		append(b[i], sb[i]);
	ans.clear(); cur = 0;
	eoln = get("\n");
	while (getline(cin, buff)) {
		append(ans, buff); cur += cnt(buff);
		ans.push_back(eoln);
	}
	while (ans.back() == eoln) ans.pop_back();
	for (map<string, int>::iterator it = id.begin(); it != id.end(); ++ it)
		s[it->second] = it->first;
}

int main() {
	init();
	while (cur < l) {
		tmp.clear();
		bool flag = false;
		for (int i = 0; i < (int)ans.size(); ++ i) {
			if (ans[i] < n) {
				append(tmp, b[ans[i]]), flag = true, cur += asc[ans[i]];
			} else tmp.push_back(ans[i]);
		}
		if (!flag) {
			puts("No result");
			return 0;
		}
		ans = tmp;
	}
	int line = 0;
	int space = 0;
	for (int i = 0; i < (int)ans.size(); ++ i) {
		if (ans[i] == eoln) {
			space = 0;
			line = 0;
			puts("");
		} else if ((int)s[ans[i]].length() + line + space > w) {
			puts("");
			printf(s[ans[i]].c_str());
			line = (int)s[ans[i]].length();
			space = 1;
		} else {
			line += (int)s[ans[i]].length() + space;
			if (space) putchar(' ');
			else space = 1;
			printf(s[ans[i]].c_str());
		}
	}
	puts("");
	return 0;
}

