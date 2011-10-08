#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cstring>
#include <set>
using namespace std;
#define two(x) (1 << (x))
#define lowbit(x) ((x)&(-(x)))

const int bound = 150, n = 16;
bool notprime[bound + 10];
int prime[bound], cnt, l2[two(16)];
vector <int> p;
vector <long long> a[two(16)], b[two(16)];
set <long long> h[two(16)];

void init() {
	for (int i = 2; i < bound; ++ i) {
		if (!notprime[i]) prime[cnt ++] = i;
		for (int j = 0; j < cnt; ++ j) {
			if (i * prime[j] >= bound) break;
			notprime[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	for (int i = 0; i < cnt; ++ i)
		if (prime[i] % 4 == 1)
			p.push_back(prime[i]);
}

inline int sqr(int a) { return a * a; }
inline int mysqrt(int a) { return (int)(sqrt(a) + 0.2); }
inline bool check(int a) { return sqr(mysqrt(a)) == a; }

int main() {
	init();
	for (int i = 1; i < two(n); ++ i)
		l2[i] = l2[i - 1] + (lowbit(i) == i);
	long long ans = 0;
	for (int i = 1; i < two(n); ++ i) {
		if (lowbit(i) == i) {
			int x = p[l2[i] - 1];
			for (int k = 0; 2 * k * k <= x; ++ k)
				if (check(x - k * k)) {
					a[i].push_back(k), b[i].push_back(mysqrt(x - k * k));
					ans += k;
				}
		}
		int x = lowbit(i), y = i ^ lowbit(i);
		for (int j = 0; j < (int)a[x].size(); ++ j)
			for (int k = 0; k < (int)a[y].size(); ++ k) {
				long long p = a[x][j] * a[y][k] + b[x][j] * b[y][k];
				long long q = a[x][j] * b[y][k] - b[x][j] * a[y][k];
				if (q < 0) q = -q;
				if (p > q) swap(p, q);
				a[i].push_back(p); b[i].push_back(q);
				ans += p;
				p = a[x][j] * b[y][k] + b[x][j] * a[y][k];
				q = a[x][j] * a[y][k] - b[x][j] * b[y][k];
				if (q < 0) q = -q;
				if (p > q) swap(p, q);
				a[i].push_back(p); b[i].push_back(q);
				ans += p;
			}
	}
	cout << ans << endl;
	return 0;
}

