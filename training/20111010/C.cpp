#include<map>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
const int MOD=10000;
using namespace std;
struct Bigint{
	int v[2003];
	Bigint(){}
	Bigint(int x){
		v[0]=1;
		v[1]=x;
	}
Bigint operator +(const Bigint &a){
	Bigint ret;
	int vv=0;
	for(int i=1;i<=max(v[0],a.v[0]);++i){
		if(v[0]>=i)vv+=v[i];
		if(a.v[0]>=i)vv+=a.v[i];
		ret.v[i]=vv%MOD;
		vv/=MOD;
	}
	ret.v[0]=max(v[0],a.v[0]);
	while(vv)ret.v[++ret.v[0]]=vv%MOD,vv/=MOD;
	return ret;
}
Bigint operator *(const Bigint &a){
	Bigint ret;
	memset(ret.v,0,sizeof(ret.v));
	for(int i=1;i<=v[0];++i)
		for(int j=1;j<=a.v[0];++j){
			ret.v[i+j-1]+=v[i]*a.v[j];
			ret.v[i+j]+=ret.v[i+j-1]/MOD;
			ret.v[i+j-1]%=MOD;
		}
	ret.v[0]=v[0]+a.v[0]-1;
	while(ret.v[ret.v[0]+1])++ret.v[0];
	return ret;
}
void out(){
	for(int i=v[0];i;--i)
		if(i==v[0])printf("%d",v[i]);
		else printf("%04d\n",v[i]);
	puts("");
}
};
map<char,Bigint> h; 
int main(){
	for(int i=0;i<10;++i)
		h['A'+i]=1;
	string s;
	while(cin>>s){
		char p=s[0];
		s.erase(s.begin());
		char q=s[s.size()-1];
		s.erase(--s.end());
		if(s=="=")h[p]=h[q];
		if(s=="+=")h[p]=h[p]+h[q];
		if(s=="*=")h[p]=h[p]*h[q];
	}
	for(map<char,Bigint>::iterator it=h.begin();it!=h.end();++it)
		it->second.out();
	return 0;
}
