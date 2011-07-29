#include<iostream>
#include<string>
#include<map>
using namespace std;
string s;
map<long long,int> h;
int main()
{
	int _;
	cin>>_;
	getline(cin,s);
	for(;_--;)
	{
		getline(cin,s);
		int n=0,cnt=0;
		h.clear();
		for(int i=0;i<s.size();)
			if(s[i]=='[')
				++cnt,++i;
			else if(s[i]==']')
				--cnt,++i;
			else
				if(s[i]>='0'&&s[i]<='9')
				{
					int tmp=0;
					while(s[i]>='0'&&s[i]<='9'&&i<s.size())
						tmp=(tmp<<1)+(tmp<<3)+s[i]-'0',++i;
					++n;
					++h[(1LL<<cnt)*tmp];
				}
			else ++i;
		int ans=0;
		for(map<long long,int>::iterator it=h.begin();it!=h.end();++it)
			if(it->second>ans)
				ans=it->second;
		cout<<n-ans<<endl;
	}
	return 0;
}
