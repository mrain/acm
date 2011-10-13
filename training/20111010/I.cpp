#include<cstdio>
#include<cstring>
#include<utility>
#include<algorithm>
using namespace std;
int n;
pair<int,int> a[100003];
int main(){
	int _,cas=0;
	for(scanf("%d",&_);_--;){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%d%d",&a[i].first,&a[i].second);
		stable_sort(a+1,a+n+1);
		int ans=a[n].first;
		int v=a[n].second;
		for(int i=n-1;i;--i){
			ans=min(ans,v+a[i].first);
			v=max(v,a[i].second);
		}
		ans=min(ans,v);
		printf("Case %d: %d\n",++cas,ans);
	}
	return 0;
}
