#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
long long myPow(int a,int b,int mod){
	long long ret=1,tmp=a;
	while(b){
		if(b&1)ret*=tmp,ret%=mod;
		tmp*=tmp;tmp%=mod;
		b>>=1;
	}
	return ret;
}
int main(){
	int n,m;
	while(scanf("%d%d",&n,&m)==2){
		long long ans=myPow(2,n,m);
		ans=(ans+1)%m;
		ans=(ans-n%m+m)%m;
		cout<<ans%m<<endl;
	}
	return 0;
}
