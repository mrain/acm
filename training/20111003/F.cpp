#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

#define maxn (110000)

const int bound = 32000;

typedef pair<int, int> PII;
multiset<int> f[maxn];
multiset<PII> g[maxn];
map<int, int> h;
map<int, int> in;
int fac[maxn];
bool flag[maxn];
char buf[100];
int m, realm;

int add(int a, int b, int mod) {
	a %= mod; b %= mod;
	return ((long long)a + b) % mod;
}

int mul(int a, int b, int mod) {
	a %= mod; b %= mod;
	return ((long long)a * b) % mod;
}

int mypow(int a, int v, int mod) {
	a %= mod;
	int t = a, ret = 1;
	while (v) {
		if (v & 1) ret = mul(ret, t, mod);
		t = mul(t, t, mod); v >>= 1;
	}
	return ret;
}

bool test(int p,int a){
//return false;
	int q=p-1;
	while(~q&1)q>>=1;
	int v=mypow(a,q,p);
	while(q!=p-1&&v!=p-1&&v!=1){
		v=(long long)v*v%p;
		q<<=1;
		//cout << v << ' ' << q << endl;
	}
	return (q&1)||v==p-1;
}

bool isPrime(int x){
//return 1;
	if (h.find(x) != h.end()) return 1;
	return 0;
	if(x==2||x==3||x==5||x==7||x==11||x==13||x==17||x==19||x==23)return 1;
	if((~x&1) || x == 1)return 0;
	//if(x<=bound)return flag[x];
	if(test(x,2)&&test(x,3))return 1;
	return 0;
}

int Pow(int x, int v) {
	int a = x, ret = 1;
	while (v) {
		if (v & 1) ret *= a;
		a *= a, v >>= 1; 
	}
	return ret;
}

void change(int now, int cnt, bool mark) {
	if (mark) {
		int size = f[now].size();
//		if (size) g[size].erase(g[size].find(Pow(fac[now], *f[now].begin())));
		if (size) g[size].erase(g[size].find(make_pair(fac[now], *f[now].begin())));
		f[now].insert(cnt);
		//g[size + 1].insert(Pow(fac[now], *f[now].begin()));
		g[size + 1].insert(make_pair(fac[now], *f[now].begin()));
	} else {
		int size = f[now].size();
		//if (size) g[size].erase(g[size].find(Pow(fac[now], *f[now].begin())));
		if (size) g[size].erase(g[size].find(make_pair(fac[now], *f[now].begin())));
		f[now].erase(f[now].find(cnt));
		//if (size - 1) g[size - 1].insert(Pow(fac[now], *f[now].begin()));
		if (size - 1) g[size - 1].insert(make_pair(fac[now], *f[now].begin()));
	}
}

void add(int x, bool mark) {
	if (!isPrime(x)) {
		for (int i = 0; i < realm && x > 1; ++i) {
			int cnt = 0, now = fac[i]; 
			while (x % now == 0) cnt++, x /= now;
		
			if (cnt == 0) continue;
			//printf("A %d %d\n", cnt, now); 
		
			change(i, cnt, mark);
			if(isPrime(x))break;
		}
	}
	
	if (x > 1) {
		//printf("A %d %d\n", 1, x);
		if (h.find(x) == h.end()) h[x] = m, fac[m ++] = x;
		x = h[x]; change(x, 1, mark);
	}
}

int main() {
	//cout << isPrime(22222227) << endl;
	for (int i = 2; i <= bound; ++i) if (!flag[i]) {
		for (int k = i; k <= bound; k += i) flag[k] = true;
		fac[m] = i; h[i] = m ++;
	} 	

	int n; scanf("%d", &n);
	
	int tot = 0,ans;
	for (int i = 0; i < n; ++i) {
		scanf("%s", buf);
		int now; scanf("%d", &now);
/*
		if(buf[0]=='+'){
			++in[now];
			if(in[now]!=1){
				printf("%d\n",ans);
				continue;
			}
		}
		else{
			--in[now];
			if(in[now]!=0){
				printf("%d\n",ans);
				continue;
			}
		}
*/

		for (int k = 0; k < m; ++k)
				
		tot += (buf[0] == '+') ? 1 : -1;
		add(now, (buf[0] == '+'));
		
		ans = 1;
		for (multiset<PII> :: iterator it = g[tot].begin(); it != g[tot].end(); ++it) ans *= Pow(it->first, it->second);
		
		printf("%d\n", ans);
	}

	return 0;
}
