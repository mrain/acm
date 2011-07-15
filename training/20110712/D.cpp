#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (100)

typedef long long LL;

LL P[maxn];
int v[maxn];

const int bound=80,from=70;

LL calc(const string& s) {
	int n=s.length();
	LL ret=0ll;
	
	for (int i=0;i<n;i++) if (s[i]=='1') ret+=P[n-i];
	
	return ret;
}

string conv(LL x) {
	string ret="";
	
	int len=0;
	memset(v,0,sizeof(v));
	for (int i=from;i>0;i--) {
		if (x>=P[i]) len=max(len,i),v[i]=1,x-=P[i];
	}
	
	if (len==0) return "0";
	
	for (int i=len;i>0;i--) ret.push_back('0'+v[i]);
	
	return ret; 
}

void outit(const string& s1,const string& s2,const string& s3){
	int len=max(s1.length(),max(s2.length(),s3.length()));

	putchar(' '),putchar(' ');
	for (int i=0;i<len-s1.length();i++) putchar(' ');
	puts(s1.c_str());
	
	putchar('+'),putchar(' ');
	for (int i=0;i<len-s2.length();i++) putchar(' ');
	puts(s2.c_str());
	
	putchar(' '),putchar(' ');
	for (int i=0;i<len;i++) putchar('-');
	puts("");
	
	putchar(' '),putchar(' ');
	for (int i=0;i<len-s3.length();i++) putchar(' ');
	puts(s3.c_str());
}

int main(){

	P[0]=P[1]=1ll;
	
	for (int i=2;i<=bound;i++) P[i]=P[i-1]+P[i-2];
	
	string s1,s2;
	while (cin >> s1 >> s2) {
		LL x=calc(s1),y=calc(s2),z=x+y;
		
		string ans1=conv(x),ans2=conv(y),ans3=conv(z);
		
		outit(ans1,ans2,ans3);
		
		puts("");
	}

	return 0;
}
