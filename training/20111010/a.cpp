#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
using namespace std;

multiset<int> s;
int n, x[110], y[110], tests;

void cut(long long &res) {
	multiset<int>::iterator it = s.end();
	-- it;
	int p = *it; s.erase(it);
	int a = p / 2, b = p - a;
	s.insert(a);
	s.insert(b);
	++ res;
}

void dub(long long &res) {
	res += *s.begin(), s.insert(*s.begin());
}

long long calc(bool flag) {
	long long ret = 0;
	while (s.size()) {
		if (flag) cut(ret), dub(ret);
		else dub(ret), cut(ret);
	}
	return ret;
}

int main() {
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++ i)
			scanf("%d%d", &x[i], &y[i]);

		s.clear();
		for (int i = 0; i < n; ++ i) if (x[i] > 1) s.insert(x[i]);
		long long ax = calc(true);
		s.clear();
		for (int i = 0; i < n; ++ i) if (y[i] > 1) s.insert(y[i]);
		long long ay = calc(false);

		printf("Case %d: %s\n", ++ ca, ax > ay ? "Alice" : "Bob");
	}
	return 0;
}
