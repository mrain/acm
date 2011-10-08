#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

#define maxn (12000)

typedef long long LL; 

const LL mod = 1000000007ll;
const int bound = 10005;

inline LL calc1(LL x) {
	return (x * (x + 1) / 2ll) % mod;
}

inline LL calc2(LL x) {
	LL ret;

	if (x % 6ll == 0ll) ret = x / 6ll * (x + x + 1ll) % mod * (x + 1ll) % mod;
	if (x % 6ll == 1ll) ret = (x + x + 1ll) * (x + 1ll) / 6ll % mod * x % mod;
	if (x % 6ll == 2ll) ret = (x + 1ll) * x / 6ll % mod * (x + x + 1ll) % mod;
	if (x % 6ll == 3ll) ret = x * (x + 1ll) / 6ll % mod * (x + x + 1ll) % mod;
	if (x % 6ll == 4ll) ret = (x + x + 1ll) * x / 6ll % mod * (x + 1ll) % mod;
	if (x % 6ll == 5ll) ret = (x + 1ll) / 6ll * x % mod * (x + x + 1ll) % mod;

	return ret;
}

inline LL calc3(LL x) {
	LL ret = calc1(x); (ret *= ret) %= mod;
	
	return ret;
}

inline LL Pow(LL x, int v) {
	LL ret = 1ll;
	while (v--) (ret *= x) %= mod;
	
	return ret;
}

map<LL, int> P2;
LL P[30];
bool flag[maxn];
int fac[maxn];
int n, m;
vector<int> f;

void ready() {
	P[0] = 1;
	for (int i = 1, k = 1; k <= n; ++i, k <<= 1) 
		P[i] = (P[i - 1] * 2ll + 4ll * calc3(k) * k % mod + 6ll * calc2(k) * Pow(k, 2) % mod + 4ll * calc1(k) * Pow(k, 3) % mod + Pow(k, 4) * k % mod) % mod;
}

LL calc4(LL x) {
	if ((x & (-x)) == x) return P[P2[x]];
	
	if (x % 2ll == 1ll) return (Pow(x, 4) + calc4(x - 1ll)) % mod;
	
	x >>= 1;
	
	return (calc4(x) * 2ll + 4ll * calc3(x) * x % mod + 6ll * calc2(x) * Pow(x, 2) % mod + 4ll * calc1(x) * Pow(x, 3) % mod + Pow(x, 4) * x % mod) % mod;
}

int main() {
	for (int i = 0, k = 1; i < 30; ++i, k <<= 1) P2[(LL)k] = i;
	
	for (int i = 2; i <= bound; ++i) if (!flag[i]) {
		fac[m++] = i;
		for (int k = i + i; k <= bound; k += i) flag[k] = true;
	}
	
	int T; scanf("%d", &T);
	
	while (T--) {
		scanf("%d", &n); ready(); 
		
		LL ans = 0ll; f.clear(); int tmp = n;
		for (int i = 0; i < m && tmp > 1; ++i) if (tmp % fac[i] == 0) {
			f.push_back(fac[i]);
			while (tmp % fac[i] == 0) tmp /= fac[i];	
		}
		if (tmp > 1) f.push_back(tmp);
			
		int tot = (int) f.size();
		//for (int i = 0; i < tot; ++i) printf("%d ", f[i]); puts("");
		
		for (int i = 0; i < 1 << tot; ++i) {
			int cnt = 0; LL now = 1ll;
			
			for (int j = 0; j < tot; ++j) 
				if (i & (1 << j)) cnt ^= 1, now *= (LL)f[j];
				
			LL x = (Pow((LL) now, 4) * calc4((LL) n / now)) % mod;
				
			if (cnt) ans -= x; else ans += x;
			
			//printf("%d %d\n", i, (int) x);
			
			while (ans < 0) ans += mod;
			while (ans >= mod) ans -= mod;
		}
		
		printf("%d\n", (int) ans);
	}

	return 0;
}
