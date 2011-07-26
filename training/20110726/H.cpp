#include<map>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include <iostream>
#include <string>
#include<cctype>
using namespace std;
map<int,int> h[300];
int sz[300];
char s[1003];
string str;
int calc(char ch)
{
	return ch;
}
int Calc(int l,int r)
{
	int ret=0;
	for(int i=l;i<=r;++i)
		ret=(ret*10)+s[i]-'0';
	return ret;
}
int Eval(int l,int r)
{
	if(s[r]==']')
	{
		int id=calc(s[l]);
		int num=Eval(l+2,r-1);
		if(num==-1||sz[id]==-1||num>=sz[id]||!h[id].count(num))
			return -1;
		else return h[id][num];
	}
	else
		return Calc(l,r);
}
int main()
{
	for(;;)
	{
		memset(sz,-1,sizeof(sz));
		for(int i=0;i<300;++i)h[i].clear();
		int ans=0;
		for(int i=1;;++i)
		{
			//if(!gets(s))return 0;
			if (!getline(cin, str)) return 0;
			strcpy(s, str.c_str());
			if(s[0]=='.')
				break;
			int len=strlen(s);
			int found=0;
			for(int j=0;j<len;++j)
				if(s[j]=='=')
					found=j;
			if(found)
			{
				int id=calc(s[0]);
				int num1=Eval(2,found-2);
				int num2=Eval(found+1,len-1);
				//printf("%d %d\n",num1,num2);
				if(num2==-1||num1==-1||sz[id]==-1||num1>=sz[id])
					(ans==0)?ans=i:0;
				else
					h[id][num1]=num2;
			}
			else
			{
				int id=calc(s[0]);
				int num=Calc(2,len-2);
				//printf("%d\n",num);
				sz[id]=num;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
