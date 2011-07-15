#include<iostream>
#include<cstring>
typedef unsigned long long ll;
using namespace std;
int one[32771];
ll a[17],b[503],low,high,f[32771];
ll gcd(ll x,ll y)
{
	ll tmp;
	while(y)
	{
		tmp=x%y;
		x=y;
		y=tmp;
	}
	return x;
}
ll calc(ll x,ll state,ll bv)
{
	ll v=1,g;
	for(int i=1;i<=a[0];++i)
		if(state&(1<<(i-1)))
		{
			g=gcd(v,a[i]);
			if(v/g>(x+a[i]-1)/a[i])
				return 0;
			v=v/g*a[i];
		}
	//cout<<state<<" "<<v<<endl;
	if(!bv)return x/v;
	g=gcd(v,bv);
	bv/=g;
	if(v>(x+bv-1)/bv)return x/v;
	else return x/v-x/(v*bv);
}
ll calc(ll x)
{
	ll v=1,g;
	for(int i=1;i<=b[0];++i)
	{
		g=gcd(v,b[i]);
		if(v/g>(x+b[i]-1)/b[i])
		{
			v=0;
			break;
		}
		v=v/g*b[i];
	}
	for(int i=1;i<(1<<a[0]);++i)
	{
		f[i]=calc(x,i,v);
		//cout<<i<<" "<<f[i]<<endl;
	}
	ll ret=0;
	for(int i=1;i<(1<<a[0]);++i)
		if(one[i]&1)
			ret+=f[i];
		else
			ret-=f[i];
	return ret;
}
int main()
{
	for(int i=1;i<32771;++i)
		one[i]=one[i-(i&(-i))]+1;
	while(cin>>a[0]>>b[0]>>low>>high,a[0]||b[0]||low||high)
	{
		for(int i=1;i<=a[0];++i)cin>>a[i];
		for(int i=1;i<=b[0];++i)cin>>b[i];
		cout<<calc(high)-calc(low-1)<<endl;
	}
	return 0;
}
