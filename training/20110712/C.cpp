#include<iostream>
#include<algorithm>
using namespace std;
long long Pow[33];
long long gcd(long long x,long long y)
{
	if(!y)return x;
	else return gcd(y,x%y);
}
void exgcd(long long a,long long b,long long &x,long long &y)
{
	if(!b)
	{
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=(a/b)*x;
}
int main()
{
	Pow[0]=1;
	for(int i=1;i<33;++i)
		Pow[i]=Pow[i-1]*2ll;
//	cout << Pow[32] << endl;
	long long a,b,c,k;
	while(cin>>a>>b>>c>>k,a+b+c+k)
	{
		k=Pow[k];
		long long g=gcd(c,k);
		long long v=b-a;
		if(v<0)v+=k;
		if(v%g)
		{
			cout<<"FOREVER"<<endl;
			continue;
		}
		long long x,y;
		exgcd(c/g,k/g,x,y);
		//cout<<x<<endl;
		x = ((x % (k/g)) + (k/g)) % (k/g);
		long long ans=(v/g*x)%(k/g);
		cout<<ans<<endl;
	}
	return 0;
}
