#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
#define two(x) (1<<(x))
#define lowbit(x) ((x)&(-(x)))

int tree[19][two(19) + 1];
multiset<long long> p;
long long offset;
int n, tests, c;
char buf[100];

void add(long long d, int s) {
	for (int i = 0; i < 18; ++ i) {
		int len = two(i + 1);
		int x = (d % len + len) % len;
		if (x == 0) x = len;
		while (x <= len) {
			tree[i][x] += s;
			x += lowbit(x);
		}
	}
}

int get(int i, int x) {
	int ret = 0;
	while (x) {
		ret += tree[i][x];
		x -= lowbit(x);
	}
	return ret;
}

int query(int i) {
	int len = two(i + 1);
	int A = two(i) - offset, B = len - 1 - offset;
	A = (A % len + len) % len;
	B = (B % len + len) % len;
	if (A == 0) A = len; if (B == 0) B = len;
	if (A <= B) return get(i, B) - get(i, A - 1);
	else return get(i, len) - get(i, A - 1) + get(i, B);
}

int main() {
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		p.clear(); offset = 0;
		memset(tree, 0, sizeof(tree));
		printf("Case %d:\n", ++ ca);
		scanf("%d", &n);
		for (int i = 0; i < n; ++ i) {
			scanf("%s%d", buf, &c);
			if (buf[0] == 'I') {
				p.insert(c - offset);
				add(c - offset, 1);
			}
			if (buf[0] == 'D') {
				if (p.count(c - offset)) add(c - offset, -p.count(c - offset)), p.erase(c - offset);
				else puts("Del error");
			}
			if (buf[0] == 'A') {
				offset += c;
			}
			if (buf[0] == 'S') {
				if (p.size() && *p.begin() + offset - c < 0)
					puts("Sub error");
				else offset -= c;
			}
			if (buf[0] == 'Q' && buf[1] == 'N') { //QNUM
				printf("%d\n", p.count(c - offset));
			}
			if (buf[1] == 'B') {
				printf("%d\n", query(c));
			}
		}
		puts("");
	}
	return 0;
}

