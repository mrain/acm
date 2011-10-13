#include<cstdio>
#include<vector>
#include<utility>
#include<cstring>
#include<iostream>
#include<map>
#include <cctype>
#include<algorithm>
using namespace std;
typedef pair<int,int> PII;
//map<int, long long> a[100003];
vector<PII> a[100003];
long long ans[500003],dx[500003];
inline bool cmp(const PII &a,const PII &b){
	if (a.first == b.first) return a.second > b.second;
	else return a.first>b.first;
}
int getint() {
	char ch; int ret = 0;
	do {
		ch = getchar();
	} while (!isdigit(ch));
	while (isdigit(ch)) {
		ret = ret * 10 + ch - '0';
		ch = getchar();
	}
	return ret;
}
int main(){
	int _,cas=0;
	for(_ = getint();_--;){
		int n,m,q;
		//scanf("%d%d%d",&n,&m,&q);
		n = getint(); m = getint(); q = getint();
		for(int i=1;i<=n;++i)a[i].clear();
		for(int i=1;i<=m;++i){
			int x,y,z;
			//scanf("%d%d%d",&x,&y,&z);
			x = getint(); y = getint(); z = getint();
			a[x].push_back(make_pair(y,z));
			//a[x][y] += z;
		}
		for(int i=1;i<=n;++i)
			if(a[i].size())
				sort(a[i].begin(),a[i].end(),cmp);
		//long long sum;
		memset(ans,0,sizeof(ans));
		//memset(dx,0,sizeof(dx));
		for(int i=1;i<=n;++i){
//			sum=0;
			for(int j=0;j<a[i].size();++j){
//				sum+=a[i][j].second;
				ans[j + 1] += a[i][j].second;
				/*long long tmp = a[i][j].second;
				int k = j;
				while (k + 1 < a[i].size() && a[i][k + 1].first == a[i][j].first) {
					++ k;
					tmp += a[i][k].second;
				}
				ans[j+1] += tmp; j = k;*/
			}
//			dx[a[i].size()+1]+=sum;
			/*int cnt = 0; int p = a[i].size();
			for (map<int, long long>::iterator it = a[i].begin(); it != a[i].end(); ++ it) {
//				cout << i << ' ' << it->first << ' ' << it->second << endl;
//				ans[++ cnt] += it->second;
				ans[p - cnt] += it->second; ++ cnt;
			}*/
		}
//		sum=0;
		for(int i=1;i<=m;++i){
//			sum+=dx[i];
//			ans[i]+=sum;
			ans[i] += ans[i - 1];
		}
		printf("Case #%d:\n",++cas);
		for(;q--;){
			int x;
			//scanf("%d",&x);
			x = getint(); x = min(x, m);
			printf("%lld\n",ans[x]);
		}
	}
	return 0;
}
