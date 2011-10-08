#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
int main(){
	string s,t;
	while(getline(cin,s)){
		for(int i=0;i<s.size();++i)
			if(s[i]>='a'&&s[i]<='z')
				t[i]=s[i]-'a'+'A';
			else if(s[i]>='A'&&s[i]<='Z')
				t[i]=s[i]-'A'+'a';
			else t[i]=s[i];
		int x=0,p=0;
		for(;p!=s.size();){
			printf("%04x:",x);
			if(p+16<=s.size()){
				for(int i=0;i<16;i+=2)
					printf(" %02x%02x",s[p+i],s[p+i+1]);
				putchar(' ');
				for(int i=0;i<16;i++)
					printf("%c",t[p+i]);
				p+=16;
			}
			else{
				int cnt=0;
				for(int i=0;p+i+1<s.size();i+=2){
					printf(" %02x%02x",s[p+i],s[p+i+1]);
					cnt+=2;
				}
				if((s.size()-p)&1){
					printf(" %02x  ",s[s.size()-1]);
					cnt+=2;
				}
				for(;cnt<=14;cnt+=2)
					printf("     ");
				putchar(' ');
				for(int i=0;p+i<s.size();i++)
					printf("%c",t[p+i]);
				p=s.size();
			}
			x+=16;
			puts("");
		}
	}
	return 0;
}
