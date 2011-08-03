#include<cstdio>
#include<iostream>
using namespace std;
const int b[]={2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
const int c[]={1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,4,1,2,3,1,2,3,4};
string s;
int main()
{
	int _,p,w;
	for(scanf("%d",&_);_--;)
	{
		scanf("%d%d",&p,&w);
		s="";
		while(s=="")getline(cin,s);
		int ans=0;
		for(int i=0;i<s.size();++i)
			if(s[i]==' ')ans+=p;
			else
			{
				if(i&&b[s[i]-'A']==b[s[i-1]-'A'])
					ans+=w;
				ans+=c[s[i]-'A']*p;
			}
		printf("%d\n",ans);
	}
	return 0;
}
