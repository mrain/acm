#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

#define maxn (10000)

typedef long long LL;

char s[maxn];
LL n;

int main(){
	int T; scanf("%d",&T);
	
	for (int tt=1;tt<=T;tt++) {
		cin >> n ; scanf("%s",s);
		
		int len=strlen(s);
		
		LL now=1ll,ans=0ll;
		for (int i=len-1;i>=0;i--) {
			(ans+=((LL)s[i]-'0')*now)%=n;
			now=(now*10ll)%n;
		}
		
		cout << ans << endl ;
	}

	return 0;
}
