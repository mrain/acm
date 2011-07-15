#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <string>
using namespace std;

struct state {
	int d[3];
	state() {
		memset(d, 0, sizeof(d));
	}
	void clear() {
		memset(d, 0, sizeof(d));
	}
	int get(int pos) {
		int &t = d[pos / 16]; pos %= 16;
		return (t >> (pos << 1)) & 3;
	}
	void set(int pos, int x) {
		int &t = d[pos / 16]; pos %= 16;
		t &= ~(3 << (pos << 1));
		t |= x << (pos << 1);
	}
	bool operator ==(const state &b) const {
		return d[0] == b.d[0] && d[1] == b.d[1] && d[2] == b.d[2];
	}
	bool operator <(const state &b) const {
		for (int i = 0; i < 3; ++ i)
			if (d[i] != b.d[i]) return d[i] < b.d[i];
		return false;
	}
};

inline int get(char c) {
	if (c == 'R') return 0;
	else if (c == 'G') return 1;
	else if (c == 'B') return 2;
	else if (c == 'Y') return 3;
	return -1;
}

char buf[3000];
state first;
state ending[30];
int m;

void genend() {
	int a[4] = {0, 1, 2, 3};
	m = 0;
	do {
		for (int i = 1; i <= 36; ++ i)
			ending[m].set(i, a[(i - 1) / 9]);
		++ m;
	} while (next_permutation(a, a + 4));
}

bool init() {
	scanf("%s", buf);
	if (buf[0] == '#') return false;
	first.set(1, get(buf[1]));
	scanf("%s", buf);
	first.set(10, get(buf[1]));
	scanf("%s", buf);
	first.set(19, get(buf[1]));
	
	scanf("%s", buf);
	for (int i = 0; i < 3; ++ i)
		first.set(2 + i, get(buf[2 * i + 1]));
	scanf("%s", buf);
	for (int i = 0; i < 3; ++ i)
		first.set(10 + i, get(buf[2 * i + 1]));
	scanf("%s", buf);
	for (int i = 0; i < 3; ++ i)
		first.set(20 + i, get(buf[2 * i + 1]));

	scanf("%s", buf);
	for (int i = 0; i < 5; ++ i)
		first.set(5 + i, get(buf[2 * i + 1]));
	for (int i = 0; i < 5; ++ i)
		first.set(14 + i, get(buf[2 * i + 12]));
	for (int i = 0; i < 5; ++ i)
		first.set(23 + i, get(buf[2 * i + 23]));

	scanf("%s", buf);
	for (int i = 0; i < 5; ++ i)
		first.set(32 + i, get(buf[2 * i + 1]));
	scanf("%s", buf);
	for (int i = 0; i < 3; ++ i)
		first.set(29 + i, get(buf[2 * i + 1]));
	scanf("%s", buf);
	first.set(28, get(buf[1]));
	return true;
}

inline void swap(state &t, int a, int b) {
	int x = t.get(a), y = t.get(b);
	t.set(a, y), t.set(b, x);
}

inline void rotate(state &t, int a, int b, int c) {
	swap(t, a, c), swap(t, a, b);
}

state applyA(state t) {
	rotate(t, 1, 10, 19);
	rotate(t, 2, 11, 20);
	rotate(t, 3, 12, 21);
	rotate(t, 4, 13, 22);
	return t;
}
state applyB(state t) {
	rotate(t, 19, 14, 32);
	rotate(t, 14, 16, 33);
	rotate(t, 18, 15, 29);
	rotate(t, 17, 21, 30);
	return t;
}
state applyC(state t) {
	rotate(t, 18, 23, 32);
	rotate(t, 16, 20, 35);
	rotate(t, 17, 24, 31);
	rotate(t, 13, 25, 30);
	return t;
}
state applyD(state t) {
	rotate(t, 5, 36, 27);
	rotate(t, 2, 33, 25);
	rotate(t, 6, 34, 26);
	rotate(t, 7, 35, 22);
	return t;
}

bool isend(const state &d) {
	for (int i = 0; i < m; ++ i)
		if (ending[i] == d) return true;
	return false;
}

map <state, int> dist;
map <state, int> pre;
queue <state> q;

void print(state cur) {
	puts("START");
	string tmp[13];
	int tc = 0;
	while (!(cur == first)) {
		int p = pre[cur];
		string t;
		switch (p / 2) {
			case 0:
				t += 'A';
				if (p & 1) {
					t += '-';
					cur = applyA(cur);
				} else {
					t += '+';
					cur = applyA(applyA(cur));
				}
				break;
			case 1:
				t += 'B';
				if (p & 1) {
					t += '-';
					cur = applyB(cur);
				} else {
					t += '+';
					cur = applyB(applyB(cur));
				}
				break;
			case 2:
				t += 'C';
				if (p & 1) {
					t += '-';
					cur = applyC(cur);
				} else {
					t += '+';
					cur = applyC(applyC(cur));
				}
				break;
			case 3:
				t += 'D';
				if (p & 1) {
					t += '-';
					cur = applyD(cur);
				} else {
					t += '+';
					cur = applyD(applyD(cur));
				}
				break;
		}
		tmp[tc ++] = t;
	}
	for (int i = tc - 1; i >= 0; -- i)
		puts(tmp[i].c_str());
	puts("END");
}

int main() {
	genend();
	while (1) {
		if (!init()) break;
		while (!q.empty()) q.pop();
		dist.clear(); pre.clear();

		bool found = false;
		dist[first] = 0; pre[first] = 0;
		q.push(first);
		while (!q.empty() && !found) {
			state cur = q.front(); q.pop();
			
			int curdist = dist[cur];

			state tmp = cur;
			for (int i = 0; i < 2; ++ i) {
				tmp = applyA(tmp);
				if (isend(tmp)) {
					pre[tmp] = i; print(tmp);
					found = true;
					break;
				}
				if (dist.find(tmp) == dist.end() && curdist < 11) {
					dist[tmp] = curdist + 1;
					pre[tmp] = i;
					q.push(tmp);
				}
			}

			if (found) break; tmp = cur;
			for (int i = 0; i < 2; ++ i) {
				tmp = applyB(tmp);
				if (isend(tmp)) {
					pre[tmp] = i + 2; print(tmp);
					found = true;
					break;
				}
				if (dist.find(tmp) == dist.end() && curdist < 11) {
					dist[tmp] = curdist + 1;
					pre[tmp] = i + 2;
					q.push(tmp);
				}
			}

			if (found) break; tmp = cur;
			for (int i = 0; i < 2; ++ i) {
				tmp = applyC(tmp);
				if (isend(tmp)) {
					pre[tmp] = i + 4; print(tmp);
					found = true;
					break;
				}
				if (dist.find(tmp) == dist.end() && curdist < 11) {
					dist[tmp] = curdist + 1;
					pre[tmp] = i + 4;
					q.push(tmp);
				}
			}
			if (found) break; tmp = cur;
			for (int i = 0; i < 2; ++ i) {
				tmp = applyD(tmp);
				if (isend(tmp)) {
					pre[tmp] = i + 6; print(tmp);
					found = true;
					break;
				}
				if (dist.find(tmp) == dist.end() && curdist < 11) {
					dist[tmp] = curdist + 1;
					pre[tmp] = i + 6;
					q.push(tmp);
				}
			}
		}
		if (!found) puts("IMPOSSIBLE");
	}
	return 0;
}
