#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define two(x) (1<<(x))

int n, a[1010], tests;
int pow[100];
map <vector<int>, double> rec;

int getrank(int st, int k) {
	int cnt = 0;
	for (int i = 0; i < k; ++ i)
		if (two(i) & st) ++ cnt;
	return cnt;
}

double solve(vector <int> b) {
	map<vector<int>, double>::iterator it = rec.find(b);
	if (it != rec.end()) return it->second;
	int n = (int)b.size();
	if (n == 1) return 0.;
	double ret = pow[n];
	for (int i = 1; i < two(n) - 1; ++ i) {
		int chk = 0;
		for (int j = 0; j < n; ++ j)
			if (i & two(j)) chk |= two(b[j]);
		if (chk != i) continue;
		vector <int> x, y;
		for (int j = 0; j < n; ++ j)
			if (i & two(j)) {
				x.push_back(getrank(i, b[j]));
			} else {
				y.push_back(getrank(i ^ (two(n) - 1), b[j]));
			}
		ret = min(ret, solve(x) + solve(y));
	}
	rec[b] = ret;
	return ret;
}

int main() {
	freopen("ds.in", "r", stdin);
	scanf("%d", &tests);
	pow[1] = 1;
	for (int i = 2; i < 12; ++ i)
		pow[i] = i * pow[i - 1];
	for (int testcase = 1; testcase <= tests; ++ testcase) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++ i) {
			scanf("%d", a + i);
			-- a[i];
		}
		vector <int> b(a, a + n);
		printf("Case #%d: %.6f\n", testcase, solve(b));
	}
	return 0;
}

