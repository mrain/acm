#include<cstdio>
#include<vector>
#include<string>
#include<sstream>
#include<iostream>
using namespace std;
vector<string> s;
const string t[]={"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
"eighteen", "nineteen", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty",
"ninety"};
int ident(int p)
{
	for(int i=0;i<20;++i)
		if(t[i]==s[p])
			return i;
	for(int i=20;i<91;i+=10)
		if(t[i/10+18]==s[p])
			return i;
}
int calc(int x,int y)
{
	if(x>y)return 0;
	int ret=0;
	if(x+1<=y&&s[x+1]=="hundred")
		ret+=100*ident(x),x+=2;
	for(int i=x;i<=y;++i)
		ret+=ident(i);
	return ret;
}
int main(){
	string x,y;
	while(getline(cin,x)){
		if(x=="")break;
		stringstream ss(x);
		s.clear();
		while(ss>>y)
			s.push_back(y);
		bool neg=false;
		while(s[0]=="negative"){
			neg^=1;
			s.erase(s.begin());
		}
		int j=0,ans=0;
		for(int i=0;i<s.size();++i)
			if(s[i]=="million")
				ans+=calc(j,i-1)*1000000,j=i+1;
			else if(s[i]=="thousand")
				ans+=calc(j,i-1)*1000,j=i+1;
		ans+=calc(j,s.size()-1);
		cout<<(neg?(-ans):ans)<<endl;
	}
	return 0;
}
