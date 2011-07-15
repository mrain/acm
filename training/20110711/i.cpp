#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

int n;
vector <vector <int> > res;
vector <int> tmp;

bool valid(const vector<int> &l) {
	bool flag = true;
	for (int i = 1; i < n; ++ i)
		if (i & 1) flag &= (tmp[i] > tmp[i - 1]) && (tmp[i] > tmp[i + 1]);
		else flag &= (tmp[i] < tmp[i - 1]) && (tmp[i] < tmp[i + 1]);
	if (flag) return true;
	flag = true;
	for (int i = 1; i < n; ++ i)
		if ((i & 1) == 0) flag &= (tmp[i] > tmp[i - 1]) && (tmp[i] > tmp[i + 1]);
		else flag &= (tmp[i] < tmp[i - 1]) && (tmp[i] < tmp[i + 1]);
	if (flag) return true;
	else return false;
}

void dfs(int d) {
	if (d == n) {
		if (valid(tmp)) res.push_back(tmp);
		return;
	}
	for (int i = 1; i < 10; ++ i) {
		tmp[d] = i;
		dfs(d + 1);
	}
}

ostream &operator << (ostream &os, const vector <int> &l) {
	os << '(';
	for (int i = 0; i < (int)l.size(); ++ i) {
		if (i) os << ',';
		os << l[i];
	}
	os << ')';
	return os;
}

int main() {
	for (int k = 3; k < 8; ++ k) {
		n = k;
		tmp.resize(k);
		dfs(0);
	}
	cout << res.size() << endl;
	return 0;
}

