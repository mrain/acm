#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <map>
using namespace std;

const int SZ = 9973;
int x[1010], y[1010], n, ans;
char buf[1000];
typedef pair<int, int> PII;


template <class T>
T abs(T a) { return a < 0 ? -a : a; }

struct hashtable {
	int size;
	int Head[10010], p[10010], Next[10010];
	PII d[10010];
	hashtable() {
		Clear();
	}
	void Clear() {
		size = 0;
		memset(Head, 0, sizeof(Head));
		memset(Next, 0, sizeof(Next));
	}
	int Find(const PII &t) {
		int value = abs(((long long)t.first + (long long)t.second * 1311713) % SZ);
		for (int q = Head[value]; q; q = Next[q])
			if (d[q] == t) return q;
		p[++ size] = 1;
		d[size] = t;
		Next[size] = Head[value];
		Head[value] = size;
		return size;
	}
	int inc(const PII &t) {
		int q = Find(t);
		return ++ p[q];
	}
}f;

void input() {
	n = 0;
	while (1) {
		gets(buf);
		if (buf[0] == '-' && buf[1] == '-') break;
		sscanf(buf, "%d%d", &x[n], &y[n]);
		++ n;
	}
}


int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

void work(int k) {
	f.Clear();
	int p = 1, q = 1;
	for (int i = 0; i < n; ++ i)
		if (i != k) {
			int a = x[i] - x[k], b = y[i] - y[k];
			if (a < 0) continue;
			if (a == 0)
				ans = max(ans, ++ p);
			else if (b == 0)
				ans = max(ans, ++ q);
			else {
				int d = abs(gcd(a, b));
				a /= d; b /= d;
				PII t = make_pair<int, int>(a, b);
				/*map <PII, int>::iterator it = f.Find(t);
				if (it == f.end()) f.insert(make_pair(t, 2)), ans = max(ans, 2);
				else ans = max(ans, ++ it->second);*/
				ans = max(ans, f.inc(t));
			}
		}
}

int main() {
	int ca = 0;
	while (1) {
		input();
		if (!n) break;
		ans = 0;
		for (int i = 0; i < n; ++ i)
			work(i);
		printf("%d. %d\n", ++ ca, ans);
	}
	return 0;
}

