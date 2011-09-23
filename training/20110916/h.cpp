#include <cstdio>
#include <set>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef pair <int, int> PII;

set <PII> vis, a, b;
PII t;
char buf[30];

bool mark(PII t, set <PII> &a, set <PII> &b) {
	vis.insert(t);
	a.insert(t);

	PII p(t.first - 1, t.second + 1), q(t.first + 1, t.second - 1);
	PII n(t.first + 1, t.second + 1), m(t.first - 1, t.second - 1);
	
	if (vis.find(p) == vis.end() && b.find(q) != b.end()) return true;
	if (vis.find(q) == vis.end() && b.find(p) != b.end()) return true;
	if (vis.find(n) == vis.end() && b.find(m) != b.end()) return true;
	if (vis.find(m) == vis.end() && b.find(n) != b.end()) return true;

	p = make_pair(t.first - 1, t.second);
	q = make_pair(t.first + 1, t.second);
	n = make_pair(t.first, t.second - 1);
	m = make_pair(t.first, t.second + 1);
	if (vis.find(p) == vis.end() && b.find(q) != b.end()) return true;
	if (vis.find(q) == vis.end() && b.find(p) != b.end()) return true;
	if (vis.find(n) == vis.end() && b.find(m) != b.end()) return true;
	if (vis.find(m) == vis.end() && b.find(n) != b.end()) return true;
	return false;
}

int main() {
	for (int i = 0; i <= 9; ++ i) {
		vis.insert(make_pair(0, i));
		vis.insert(make_pair(i, 0));
		vis.insert(make_pair(9, i));
		vis.insert(make_pair(i, 9));
	}
	for (int i = 0; i < 32; ++ i) {
		scanf("%s", buf);
		t.first = buf[0] - 'a' + 1;
		sscanf(buf + 1, "%d", &t.second);
		bool xx;
		if (i & 1) xx = mark(t, a, b);
		else xx = mark(t, b, a);
		if (xx) {
			printf("%d\n", i + 1);
			goto END;
		}
	}
	puts("Draw");
END:;
	return 0;
}

