#include<cstdio>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
int k;
long long e,t,l,r;
long double ans=0,p;
char s[101];
const long double eps=1e-7;
void work(int u,long double l,long double r,long double ll,long double rr,long double pp){
	if(ll>r||rr<l)return;
	if(l+eps>ll&&rr+eps>r){
		ans+=pp;
		return;
	}
	long double mid=(l+r)/2.0;
	if(u==k){
		if(mid+eps>ll&&rr+eps>mid)
			ans+=pp;
		return;
	}
	work(u+1,l,mid,ll,rr,pp*(mid+eps>t?1-p:p));
	work(u+1,mid,r,ll,rr,pp*(mid+eps>t?p:1-p));
}

void input(long long &a) {
	//cin >> s;
	scanf("%s", s);
	int l = strlen(s), cnt = 0;
	bool flag = false;
	a = 0;
	for (int i = 0; i < l; ++ i) {
		if (s[i] == '.') flag = true;
		else {
			a = a * 10 + (s[i] - '0');
			if (flag) ++ cnt;
		}
	}
	while (cnt < 12) {
		a *= 10;
		++ cnt;
	}
}

int main(){
	cout.setf(ios::fixed);
	cout.precision(9);
	//scanf("%d%d%d",&k,&r,&l);
	cin >> k >> r >> l >> p;
	input(e); input(t);
	for (int i = 0; i < 12; ++ i) r *= 10, l *= 10;
	//cout << e << endl;
	//scanf("%lf%lf%lf",&p,&e,&t);
	//cout << k << ' ' << r << ' ' << l << ' ' << p << ' ' << e << ' ' << t << endl;
	work(0,r,l,t-e,t+e,1);
	//printf("%.6f\n",ans);
	cout << ans << endl;
	return 0;
}
