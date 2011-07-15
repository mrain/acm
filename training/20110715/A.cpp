#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

#define maxn (1100000)

typedef long long LL;

const int bound=1000005;

bool flag[maxn];
LL prime[maxn];
int c;

LL ans;

void ready(){
	for (int i=2;i<=bound;i++) if (!flag[i]) {
		prime[++c]=(LL)i;
		for (int k=i+i;k<=bound;k+=i) flag[k]=true;
	}
}

LL calc(LL a,LL b) {
	if (a<b) return 0ll;
	
	return a/b+calc(a/b,b);
}

int main(){
	ready();

	int T; scanf("%d",&T);
	
	while (T--) {
		LL x,y; cin >> x >> y ;
		
		ans = -1;
		
		for (int i=1;i<=c;i++) {
			LL sum=0ll;
			
			while (y%prime[i]==0) sum++,y/=prime[i];
			
			if (sum>0ll) {
				LL v=calc(x,prime[i]); v/=sum;
				
				if (ans==-1||ans>v) ans=v;
			}
			
		}
		
		if (y>1ll) {
			LL v=calc(x,y);
				
			if (ans==-1||ans>v) ans=v;
		}
		
		if (ans<0ll) ans=0ll;
		
		cout << ans << endl ;
	}

	return 0;
}
