#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
int main(){
	string s;
	int cas=0,_;
	for(cin>>_,getline(cin,s);_--;){
		getline(cin,s);
		printf("Case #%d: ",++cas);
		int i=0;
		while(s[i]!='/')++i;
		for(i+=2;s[i]!=':'&&s[i]!='/'&&i!=s.size();++i)
			putchar(s[i]);
		puts("");
	}
	return 0;
}
