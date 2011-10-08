#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <iostream>
using namespace std;

#define maxn (200)
#define A first
#define B second

typedef long long LL;

LL C[maxn][maxn];
LL P[maxn];

const LL mod = 1000000007ll;
const int bound = 100;

void ready() {
	C[0][0] = 1ll;
	for (int i = 1; i <= bound; ++i) {
		C[i][0] = 1ll;
		for (int j = 1; j <= i; ++j) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	}
	
	P[0] = 1ll;
	for (LL i = 1ll; i <= (LL) bound; ++i) P[i] = (P[i - 1] * i) % mod;
}

map<int, LL> F[maxn];
int n, k;

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

inline LL Lcm(int a, int b) {
	return a / gcd(a, b) * b;
}

void work() {
/*
	memset(F, 0, sizeof(F)); F[0] = 1ll;
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) {
			if (k % j != 0 || j > n - i + j) continue;
			
			printf("%d %d %d %d\n", j, (int) F[i - j], (int) C[n - i + j - 1][j - 1], (int) P[j - 1]);
			
			(F[i] += F[i - j] * C[n - i + j - 1][j - 1] % mod * P[j - 1] % mod) %= mod;
		}
		
		printf("F[%d] = %d\n", i, (int) F[i]);
	}
*/
	for (int i = 0; i <= n; ++i) F[i].clear();
	F[0][1] = 1ll;
	
	for (int i = 0; i < n; ++i) {
		for (map<int, LL>::iterator it = F[i].begin(); it != F[i].end(); ++it) {
			int j = it->A;
			LL v = it->B; if (v == 0ll) continue;
			
			for (int a = 1; a <= n - i; ++a) {
				int p = Lcm(j, a);
				if (k % p != 0) continue;
//				F[i + a][p] += v * C[n - i - 1][a - 1] * P[a - 1];
				(F[i + a][p] += v * C[n - i - 1][a - 1] % mod * P[a - 1] % mod) %= mod;
			}
		}
	}

//	for (map<int, LL>::iterator it = F[n].begin(); it != F[n].end(); ++it)
//		cout << it->first << endl;
//	cout << F[n].size() << endl;
	printf("%d\n", (int)F[n][k]);
}

int main() {
	ready();

	int T; scanf("%d", &T);// T = 1;
	
	for (int cases = 1; cases <= T; ++cases) {
		printf("Case %d: ", cases);
		scanf("%d%d", &n, &k);
		//n = 2 + 3 + 5 + 7 + 11 + 13 + 17 + 19 + 23, k = 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23;//k = 203693490;
		work();	
	}

	return 0;
}
