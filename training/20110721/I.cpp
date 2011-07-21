#include<cstdio>
#include<string>
#include<cctype>
#include<cstring>
#include<iostream>
using namespace std;
string a[]={"","I","II","III","IV","V","VI","VII","VIII","IX"};
string b[]={"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
string c[]={"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
char s[10003];
int main()
{
	while(gets(s))
	{
		int len=strlen(s);
		if(!len)continue;
		for(int i=0;i<len;++i)
			s[i]=toupper(s[i]);
		int last=0,ans=0;
		for(int i=last;i<len;++i)
			if(s[i]=='M')
				ans+=1000,last=i+1;
		for(int i=9;i;--i)
		{
			int k=0;
			bool OK=false;
			for(int j=last;j<len;++j)
			{
				if(s[j]==c[i][k])++k;
				if(k==c[i].size())
				{
					last=j+1;
					OK=true;	
					break;
				}
			}
			if(OK)
			{
				ans+=i*100;
				break;
			}
		}
		for(int i=9;i;--i)
		{
			int k=0;
			bool OK=false;
			for(int j=last;j<len;++j)
			{
				if(s[j]==b[i][k])++k;
				if(k==b[i].size())
				{
					last=j+1;
					OK=true;	
					break;
				}
			}
			if(OK)
			{
				ans+=i*10;
				break;
			}
		}
		for(int i=9;i;--i)
		{
			int k=0;
			bool OK=false;
			for(int j=last;j<len;++j)
			{
				if(s[j]==a[i][k])++k;
				if(k==a[i].size())
				{
					last=j+1;
					OK=true;	
					break;
				}
			}
			if(OK)
			{
				ans+=i;	
				break;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
