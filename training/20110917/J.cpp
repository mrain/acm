#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
const int MOD=1000000007;
struct matrix{
	int l[4][4];
	matrix(){};
	matrix operator *(const matrix &a){
		matrix ret;
		memset(ret.l,0,sizeof(ret.l));
		for(int i=0;i<4;++i)
			for(int j=0;j<4;++j)
				for(int k=0;k<4;++k){
					long long tmp=1LL*l[i][j]*a.l[j][k]%MOD;
					ret.l[i][k]+=tmp;
					if(ret.l[i][k]>=MOD)ret.l[i][k]-=MOD;
				}
		return ret;
	}
};
int calc(int x,int y,int len){
	matrix ret,tmp;
	for(int i=0;i<4;++i)
		for(int j=0;j<4;++j){
			tmp.l[i][j]=(i!=j);
			ret.l[i][j]=(i==j);
		}
	while(len){
		if(len&1)ret=ret*tmp;
		tmp=tmp*tmp;
		len>>=1;
	}
	return ret.l[x][y];
}
int work(vector< pair<int,int> > &h){
	vector< pair<int,int> > t=h;
	stable_sort(t.begin(),t.end());
	long long ret=1;
	for(int i=0;i<t.size()-1;++i){
		ret*=calc(t[i].second,t[i+1].second,t[i+1].first-t[i].first);
		ret%=MOD;
	}
	return ret;
}
int n,m;
vector< pair<int,int> > h;
int main(){
	while(scanf("%d%d",&n,&m)==2){
		h.clear();
		for(int i=0;i<m;++i){
			int x;char ch[5];
			scanf("%d%s",&x,ch);
			h.push_back(make_pair(x,ch[0]-'A'));
		}
		if(n==1){
			if(m)puts("1");
			else puts("4");
			continue;
		}
		if(h.size())stable_sort(h.begin(),h.end());
		int s1=(h.size()&&h[0].first==1)?h[0].second:0;
		int t1=(h.size()&&h[0].first==1)?h[0].second:3;
		int s2=(h.size()&&h[m-1].first==n)?h[m-1].second:0;
		int t2=(h.size()&&h[m-1].first==n)?h[m-1].second:3;
		if(h.size()&&(h.begin())->first==1)h.erase(h.begin());
		if(h.size()&&(--h.end())->first==n)h.erase(--h.end());
		int ans=0;
		for(int i=s1;i<=t1;++i)
			for(int j=s2;j<=t2;++j){
				h.push_back(make_pair(1,i));
				h.push_back(make_pair(n,j));
				ans+=work(h);
				if(ans>=MOD)ans-=MOD;
				h.erase(--h.end());
				h.erase(--h.end());
			}
		printf("%d\n",ans);
	}
	return 0;
}
