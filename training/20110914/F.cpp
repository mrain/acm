#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const long long maxv=10000000000LL;
long long a[5000003];
int main(){
	int l=0,r=0;
	a[r++]=0;
	a[r++]=1;
	a[r++]=2;
	a[r++]=3;
	while(l!=r){
		long long x=a[l++];
		if(!x)continue;
		x*=10;
		if(x<=maxv)a[r++]=x;
		if(x+1<=maxv)a[r++]=x+1;
		if(x+2<=maxv)a[r++]=x+2;
		if(x+3<=maxv)a[r++]=x+3;
	}
	int cnt=0;
	for(int i=0;i<r;++i)
		if(a[i]%10!=3)
			a[cnt++]=a[i];
	for(int i=cnt-11;i<cnt;++i)
		cout<<a[i]<<endl;
	long long n;
	while(cin>>n)
		cout<<lower_bound(a,a+cnt,n)-a<<endl;
	return 0;
}
