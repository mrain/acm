#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
string a,b;
int f[103][103][29];
int DP(int l,int r,char col){
	if(f[l][r][col]!=-1)return f[l][r][col];
	if(l>r)return 0;
	if(l==r)
		if(col)return b[l]!='a'+col-1;
		else return a[l]!=b[l];
	int &ret=f[l][r][col];
	ret=(~0U>>1);
	
	for(int i=l;i<r;++i)
		ret=min(ret,DP(l,i,col)+DP(i+1,r,col));
	
	int ll=l;
	while(b[ll]==b[ll+1]&&ll<=r)++ll;
	ret=min(ret,DP(ll,r,b[ll]-'a'+1)+1);
	
	int rr=r;
	while(b[rr]==b[rr-1]&&rr>=l)--rr;
	ret=min(ret,DP(l,rr,b[rr]-'a'+1)+1);
	
	return ret;
}
int main(){
	while(cin>>a){
		cin>>b;
		memset(f,-1,sizeof(f));
		int ans=DP(0,a.size()-1,0);
		ans=min(ans,DP(0,a.size()-1,b[0]-'a'+1)+1);
		ans=min(ans,DP(0,a.size()-1,b[b.size()-1]-'a'+1)+1);
		cout<<ans<<endl;
	}
	return 0;
}
