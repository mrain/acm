#include<cstdio>
#include<set>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
using namespace std;
int n;
char s[100003];
bool email[100003];
vector<string> a,b;
set< vector<string> > h,h1;
bool isdevide(int pos)
{
	pos=s[pos];
	if(pos>=9&&pos<=13)return true;
	if(pos==32)return true;
	if(pos==33||pos==44||pos==46||pos==58||pos==59||pos==63)return true;
	return false;
}
bool isemailch(char ch)
{
	if(ch>='a'&&ch<='z')return true;
	if(ch>='A'&&ch<='Z')return true;
	if(ch>='0'&&ch<='9')return true;
	if(ch=='-'||ch=='_')return true;
	if(ch=='.')return true;
	return false;
}
void work(vector<string> &u)
{
	gets(s);
	//printf("%s\n",s);
	int len=strlen(s);
	memset(email,0,len+1);
	for(int i=0;i<len;++i)
		if(s[i]=='@')
		{
			int j=i,k=i;
			if(s[j-1]!='.')
				while(isemailch(s[j-1])&&j>0&&!email[j-1])--j;
			if(s[k+1]!='.')
				while(isemailch(s[k+1])&&k+1<len)
				{
					if(s[k]=='.'&&s[k+1]=='.')break;
					++k;
				}
			while(s[j]=='.')++j;
			while(s[k]=='.')--k;
			bool found_per=false;
			for(int l=i+1;l<=k;++l)
				if(s[l]=='.')
				{
					found_per=true;
					break;
				
				}
			if(!found_per||j==i)
			{
				i=k;	
				continue;
			}
			i=k;
			for(int l=j;l<=k;++l)
				email[l]=true;
		}
	string t="";
	for(int i=0;i<=len;)
		if(email[i]){
			if(t!="")
			{
				u.push_back(t);
				t="";
			}
			while(email[i])
				t+=s[i],++i;
			u.push_back(t);
			t="";
		}
		else if(isdevide(i)||i==len){
			if(t!="")u.push_back(t);
			t="";
			++i;
		}
		else
			t+=s[i++];
}
int main()
{
	//freopen("H.in","r",stdin);
	int testcase;
	for(scanf("%d",&testcase);testcase--;)
	{
		scanf("%d",&n);
		int k,l;
		scanf("%d%d%*c",&k,&l);
		a.clear(),b.clear();
		for(int i=0;i<k;++i)
			work(a);/*
		for(int i=0;i<a.size();++i)
		{
			cout<<a[i];
			if(i==a.size()-1)puts("");
			else putchar(' ');
		}*/
		for(int i=0;i<l;++i)
			work(b);/*
		for(int i=0;i<b.size();++i)
		{
			cout<<b[i];
			if(i==b.size()-1)puts("");
			else putchar(' ');
		}*/
		h.clear(),h1.clear();
		for(int i=0;i+n<=a.size();++i)
		{
			vector<string> t;
			t.clear();
			for(int j=0;j<n;++j)
				t.push_back(a[i+j]);
			h.insert(t);
		}
		int ans=0;
		for(int i=0;i+n<=b.size();++i)
		{
			vector<string> t;
			t.clear();
			for(int j=0;j<n;++j)
				t.push_back(b[i+j]);
			if(!h1.count(t))
			{
				h1.insert(t);
				if(h.count(t))
				//cout<<t[0]<<endl;
					++ans;
			}
		}
		//printf("%d\n",ans);
		//printf("%d %d\n",h.size(),h1.size());
		int cnt=max(h.size(),h1.size());
		printf("%.2f\n",100.0*ans/cnt);
	}
	return 0;
}
