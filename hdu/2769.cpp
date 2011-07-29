#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (1000)

const int mod=10001;

int g[maxn];
int n,a,b;

int Gcd(int x,int y) {
	return x == 0 ? y : Gcd(y%x,x);
}

void e_gcd(int a,int b,int& x,int& y) {
	if (b==0) {
		x=1,y=0;
		
		return ;
	}
	
	e_gcd(b,a%b,x,y);
	int tmp=x;
	x=y; y=tmp-a/b*y;
}

int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&g[i]);
	
	for (a=0;a<mod;a++) {
		int x=(mod-((((a*a)%mod)*g[1])%mod)+g[2])%mod,t=(a+1)%mod;
	
		bool flag=true;
		for (int i=2;i<n&&flag;i++) 
			if ((mod-((((a*a)%mod)*g[i])%mod)+g[i+1])%mod != x) flag=false;
			
		if (!flag) continue;
		
		int GCD=Gcd(t,mod);
		
		if (x%GCD!=0) continue;
		t/=GCD,x/=GCD; int v=mod/GCD;
		
		int b,k;
		e_gcd(t,v,b,k);
		
		b=((b%v)+v)%v;
		(b*=x)%=mod;
		
		for (int i=1;i<=n;i++) printf("%d\n",(a*g[i]+b)%mod);
		
		break;
	}

	return 0;
}
