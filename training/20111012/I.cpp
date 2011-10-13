#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int inf=(~0U>>2);
int n,a[50],f[203][203],vis[203],nt[203],cnt[203];
int solve(int l,int r){
	//printf("%d %d\n",l,r);
	if(l>r)return 0;
	if(cnt[r]-cnt[l-1]<2)return 0;
	if(f[l][r]!=-1)return f[l][r];
	int &ret=f[l][r];
	ret=inf;
	for(int i=l;i<=r;++i){
		int v=i;
		if(nt[v]>r)continue;
		if(i==l&&!nt[v])continue;
		if(nt[v])
			ret=min(ret,max(solve(l,i-1),max(solve(i+1,nt[v]-1),solve(nt[v],r)))+1);
		else
			ret=min(ret,max(solve(l,i-1),solve(i,r))+1);
		//ret=min(ret,max(solve(l,i-1),max(solve(i+1,nt[v]-1),solve(nt[v]?nt[v]:i,r)))+1);
	}
	//printf("%d %d %d\n",l,r,ret);
	return ret;
}
int main(){
	int _,cas=0;
	for(scanf("%d",&_);_--;){
		scanf("%d",&n);
		for(int i=1;i<=2*n;++i)
			scanf("%d",a+i);
		memset(f,-1,sizeof(f));
		memset(vis,0,sizeof(vis));
		memset(cnt,0,sizeof(cnt));
		memset(nt,0,sizeof(nt));
		for(int i=1;i<=2*n;++i)
			if(vis[a[i]]){
				nt[vis[a[i]]]=i;
				cnt[i]=1;
			}
			else
				vis[a[i]]=i;
		for(int i=1;i<=2*n;++i)
			cnt[i]+=cnt[i-1];
		printf("Case #%d: %d\n",++cas,solve(1,2*n));
	}
	return 0;
}
/*
5 8 1073741823
3 8 1073741823
1 4 1
1 5 1
1 8 1073741823
Case #3: 1073741823*/

