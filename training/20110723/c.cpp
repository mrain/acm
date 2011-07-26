#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int mod = 1000000007;
typedef pair<int, int> PII;
typedef pair<int, PII> PIII;
map <PIII, int> hash1, hash2;
int m, cnt, cnt2;
vector <PIII> l1, l2;
int f1[51][2500], f[51][2500];
int p[51][51], a[51][51], c[51][51];
long long l;

inline void add(int &a, int b) {
	a = ((long long)a + b) % mod;
}

inline int plus(int a, int b) {
	return ((long long)a + b) % mod;
}

inline int mul(int a, int b) {
	return ((long long)a * b) % mod;
}

inline PIII make(int a, int b, int c) {
	return make_pair(a, make_pair(b, c));
}

void dp1(const PIII &start) {
	static int f[51][2500];
	memset(f, 0, sizeof(f));
	int first = hash1[start];
	f[0][first] = 1;
	for (int i = 0; i < m; ++ i)
		for (int j = 0; j < cnt; ++ j)
			if (f[i][j]) {
				int a = l1[j].first, b = l1[j].second.first, c = l1[j].second.second;
				if (a > 1) add(f[i + 1][hash1[make(a - 1, b + 1, c)]], mul(f[i][j], a));
				else add(f[i + 1][hash1[make(b + 1, c, 0)]], f[i][j]);
				if (b) add(f[i + 1][hash1[make(a, b - 1, c + 1)]], mul(f[i][j], b));
			}
	for (int i = 0; i < cnt2; ++ i)
		p[hash2[start]][i] = f[m][hash1[l2[i]]];
}

void prepare() {
	hash1.clear();
	hash2.clear();
	cnt = 0; cnt2 = 0;
	for (int a = 0; a <= m; ++ a)
		for (int b = 0; b <= m; ++ b)
			for (int c = 0; c <= m; ++ c) {
				if (a + b + c != m) continue;
				l1.push_back(make(a, b, c));
				hash1[make(a, b, c)] = cnt ++;
				if (a != 0 && (2 * c + b) % m == 0) {
					//cout << a << ' ' << b << ' ' << c << endl;
					hash2[make(a, b, c)] = cnt2 ++;
					l2.push_back(make(a, b, c));
				}
			}
	for (int i = 0; i < (int)l2.size(); ++ i)
		dp1(l2[i]);
}

void pow(long long t) {
	memset(a, 0, sizeof(a));
	for (int i = 0; i < cnt2; ++ i)
		a[i][i] = 1;
	while (t) {
		if (t & 1ll) {
			memset(c, 0, sizeof(c));
			for (int i = 0; i < cnt2; ++ i)
				for (int j = 0; j < cnt2; ++ j)
					for (int k = 0; k < cnt2; ++ k)
						add(c[i][j], mul(a[i][k], p[k][j]));
			memcpy(a, c, sizeof(a));
		}
		memset(c, 0, sizeof(c));
		for (int i = 0; i < cnt2; ++ i)
			for (int j = 0; j < cnt2; ++ j)
				for (int k = 0; k < cnt2; ++ k)
					add(c[i][j], mul(p[i][k], p[k][j]));
		memcpy(p, c, sizeof(p));
		t /= 2;
	}
}

int main() {
	cin >> l >> m;
	prepare();
/*	for (int i = 0; i < cnt2; ++ i){
		for (int j = 0; j < cnt2; ++ j)
			cout << p[i][j] << ' ';
		cout << endl;
	}*/
	long long times = l / m;
	pow(times);
/*	for (int i = 0; i < cnt2; ++ i){
		for (int j = 0; j < cnt2; ++ j)
			cout << a[i][j] << ' ';
		cout << endl;
	}*/
	// lastdp
	l %= m;
	memset(f, 0, sizeof(f));
	int tmp_sp2 = hash2[make(m, 0, 0)];
	for (int i = 0; i < cnt2; ++ i)
		f[0][hash1[l2[i]]] = a[tmp_sp2][i];
	for (int i = 0; i < l; ++ i)
		for (int j = 0; j < cnt; ++ j)
			if (f[i][j]) {
				int a = l1[j].first, b = l1[j].second.first, c = l1[j].second.second;
				if (a > 1) add(f[i + 1][hash1[make(a - 1, b + 1, c)]], mul(f[i][j], a));
				else add(f[i + 1][hash1[make(b + 1, c, 0)]], f[i][j]);
				if (b) add(f[i + 1][hash1[make(a, b - 1, c + 1)]], mul(f[i][j], b));
			}
	int ans = 0;
	for (int i = 0; i < cnt; ++ i)
		add(ans, f[l][i]);
	cout << ans << endl;
	return 0;
}

