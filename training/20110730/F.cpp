#include <iostream>
#include <cmath>

using namespace std;

typedef long long LL;

LL Gcd(LL x,LL y) {
	return x==0ll ? y : Gcd(y%x,x);
}

int main(){
	LL x,y,h;
	
	while (cin >> h >> x >> y) {
		if (h==0ll) {
			cout << 0 << endl ; continue;
		}
	
		LL dx=x,dy=y-h;
		LL step=Gcd(dx,dy);
		
		//cout << step << endl ;
		
		LL d=dx-dy-1ll;
		dx/=step,dy/=step;
		LL n=d/(dx-dy);
		
		//cout << "Steps : " << n << endl ;
		
		dx*=n,dy*=n;
		LL ans=((1ll+dx)*(1ll+dy)+n+1ll)/2ll;
		ans+=(h-1ll)*(dx+1ll);
		ans-=(dx*dx+dx)/2ll;
		
		//cout << ans << endl ;
		
		for (LL i=dx+1ll;i<=x;i++) {
			LL v=h+((y-h)*i/x);
			//cout << i << ' ' << v << endl ;
			
			if (v<=i) break;
			
			ans+=v-i;
		}
		
		cout << ans << endl ;
	}

	return 0;
}

