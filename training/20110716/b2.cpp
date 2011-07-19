#include<cstdio>
#include<cstring>
#include<iostream>
//                                    Last Change:  2011-07-16 10:35:07
using namespace std;
int n,ans,g[11],f[257][257];
int search(int state,int last)
{
	if(f[state][last]!=-1)
		return f[state][last];
	if(state==(1<<n)-1)
		return 1;
	int &ret=f[state][last];
	ret=0;
	for(int i=0;i<n;++i)
		if(last&(1<<i))
		{
			for(int j=0;j<(1<<n);++j)
			{
				if(state&j)continue;
				if((g[i]&j)==j)
					ret+=search(state|j,(last-(1<<i))|j);
			}
			break;
		}
	return ret;
}
int main()
{
	while(scanf("%d",&n),n)
	{
		for(int i=0;i<n;++i)
		{
			g[i]=0;
			for(int j=0;j<n;++j)
			{
				char ch=' ';
				while(ch!='0'&&ch!='1')ch=getchar();
				if(ch=='1')
					g[i]|=(1<<j);
			}
		}
		ans=0;
		memset(f,-1,sizeof(f));
		for(int i=0;i<n;++i)
			ans+=search(1<<i,1<<i);
		cout<<ans<<endl;
	}
	return 0;
}
