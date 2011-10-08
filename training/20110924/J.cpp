#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1000003;
const int MOD=1000000007;
int fib[N],fir[N],cnt[N];
bool np[N];
int main(){
	for(int i=2;i<N;++i)
		if(!np[i]){
			fir[i]=i;
			for(long long j=1LL*i*i;j<N;j+=i)
				fir[j]=i,np[j]=1;
		}
	fib[0]=fib[1]=1;
	for(int i=2;i<N;++i){
		fib[i]=fib[i-1]+fib[i-2];
		if(fib[i]>=MOD)fib[i]-=MOD;
	}
	int n;
	scanf("%d",&n);
	for(int i=2;i<=n;++i){
		cnt[i]+=fib[n-i];
		if(cnt[i]>=MOD)cnt[i]-=MOD;
	}
	long long ans=1;
	for(int i=n;i>1;--i)
		if(fir[i]==i)
			ans*=(cnt[i]+1),ans%=MOD;
		else{
			cnt[i/fir[i]]+=cnt[i];
			if(cnt[i/fir[i]]>=MOD)cnt[i/fir[i]]-=MOD;
			cnt[fir[i]]+=cnt[i];
			if(cnt[fir[i]]>=MOD)cnt[fir[i]]-=MOD;
			cnt[i]=0;
		}
	cout<<ans<<endl;
	return 0;
}
