#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

typedef int LL;

LL k,n,xs,ys,xe,ye;

LL gcd(LL x,LL y) {
	return y == 0ll ? x : gcd(y, x % y);
}

int main(){
	int T; scanf("%d",&T);
	
	while (T--) {
		scanf("%d%d%d%d%d%d",&k,&n,&xs,&ys,&xe,&ye);
		
		if (k>n) swap(k,n);
		
		LL m=gcd(k,n);
		
		/*if ((xe-xs)%m==0ll&&(ye-ys)%m==0ll) puts("TAK");
		else puts("NIE");*/
		LL x = xe - xs, y = ye - ys;
		if (x % m != 0 || y % m != 0) puts("NIE");
		else {
			x /= m, y /= m, k /= m, n /= m;
			if (k & n & 1) puts(((x + y) & 1) == 1 ? "NIE" : "TAK");
			else puts("TAK");
		}
	}

	return 0;
}
