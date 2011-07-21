#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int p[501];
bool np[501];
int calc(int v,int p)
{
	int ret=0;
	while(v)
	{
		ret+=v/p;
		v/=p;
	}
	return ret;
}
int main()
{
	for(int i=2;i<501;++i)
		if(!np[i])
			for(int j=i*i;j<501;j+=i)
				np[j]=true;
	for(int i=2;i<501;++i)
		if(!np[i])
			p[++p[0]]=i;
	int n,k;
	while(scanf("%d%d",&n,&k)==2)
	{
		long long ans=1;
		for(int i=1;i<=p[0]&&p[i]<=n;++i)
		{
			int tmp=calc(n,p[i])-calc(k,p[i])-calc(n-k,p[i]);
			ans*=(tmp+1);
		}
		cout<<ans<<endl;
	}
	return 0;
}
