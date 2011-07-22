#include<cstdio>
#include<cmath>
#include<iostream>
#include<map>
using namespace std;
typedef long long ll;
map<ll,ll> h;
bool MyPow(const ll &a,int b,const ll &comp)
{
	ll ret=1,tmp=a;
	while(b)
	{
		if(b&1)
		{
			if(ret>comp/tmp)
				return true;
			else	
				ret*=tmp;
		}
		if(b>1&&tmp>comp/tmp)
			return true;
		else
			tmp*=tmp;
		b>>=1;
	}
	return false;
}
ll MySqx(const ll &a,const int &x)
{
	ll l=1,r=1LL<<62;
	while(l!=r)
	{
		ll mid=l+r+1>>1;
		if(MyPow(mid,x,a))
			r=mid-1;
		else
			l=mid;
	}
	return l;
}
ll f(const ll &x)
{
	if(h.count(x))return h[x];
	if(x<4)return x-1;
	ll ret=x-1;
	for(int i=2;(1LL<<i)<=x;++i)
		ret-=f(MySqx(x,i));
	h[x]=ret;
	return ret;
}
ll work(const ll &x)
{
	ll ret=f(x);
	//cout<<ret<<endl;
	for(int i=2;(1LL<<i)<=x;++i)
	{
		ll tmp=i*f(MySqx(x,i));
		ret+=tmp;
		//cout<<i<<" "<<tmp/i<<endl;
	}
	return ret;
}
int main()
{
	ll x,y;
	while(cin>>x>>y,x+y)
		cout<<work(y)-work(x-1)<<endl;
	return 0;
}
