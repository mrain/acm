#include<set>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long ll;
int n;
vector<int> a[16];
set<ll> h;
int DFS(int fa,int u,int v){
	int ret=1;
	for(int i=0;i<a[u].size();++i){
		int y=a[u][i];
		if(y==fa)continue;
		if(v&(1<<y-1))
			ret+=DFS(u,y,v);
	}
	return ret;
}
ll DFS2(int fa,int u,int v){
	ll r1=1,r2=1LL;
	for(int i=0;i<a[u].size();++i){
		int y=a[u][i];
		if(y==fa)continue;
		if(v&(1<<y-1)){
			ll tmp=DFS2(u,y,v);
			r1+=tmp*tmp;
			r2*=tmp;
		}
	}
	return r1*19930912+r2;
}
void check(int v){
//cout << v << endl;
	int cnt=0;
	for(int i=1;i<=n;++i)
		if(v&(1<<i-1))
			++cnt;
	for(int i=1;i<=n;++i)
		if(v&(1<<i-1)){
			int tmp=DFS(0,i,v);
			if(tmp!=cnt)return;
		}
	ll ans=-1;
	for(int i=1;i<=n;++i)
		if(v&(1<<i-1)){
			ll tmp=DFS2(0,i,v);
			if(ans==-1||ans<tmp)ans=tmp;
		}
	//printf("%d %lld\n",v,ans);
	h.insert(ans);
}
int main(){
	int _,cas=0;
	for(scanf("%d",&_);_--;){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
			a[i].clear();
		h.clear();
		for(int i=1;i<=n-1;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			a[x].push_back(y);
			a[y].push_back(x);
		}
		for(int i=1;i<(1<<n);++i)
			check(i);
		printf("Case #%d: %d\n",++cas,h.size());
	}
	return 0;
}
