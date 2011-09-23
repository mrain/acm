#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,a[31][31],f[9],g[9];
vector<int> h[31];
long long solve(vector<int> &s){
	memset(f,0,sizeof(f));
	for(int i=0;i<h[s[0]].size();++i)
		f[h[s[0]][i]]=1;
	for(int i=1;i<s.size();++i){
		memcpy(g,f,sizeof(g));
		memset(f,0,sizeof(f));
		for(int j=0;j<8;++j)
			for(int k=0;k<h[s[i]].size();++k)
				f[h[s[i]][k]^j]+=g[j];
	}
	return f[0];
}
int main(){
    int _;
	for(scanf("%d",&_);_--;){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				scanf("%d",a[i]+j);
		for(int i=1;i<=m;++i){
			h[i].clear();
			int k;
			for(scanf("%d",&k);k--;){
				int x;
				scanf("%d",&x);
				h[i].push_back(x);
			}
		}
		long long ans=1LL;
		for(int i=1;i<=m;++i){
			int k=n+1;
			for(int j=i;j<=n;++j)
				if(a[j][i]){
					k=j;
					break;
				}
			if(k>n){
				ans*=h[i].size();
				continue;
			}
			if(k!=i){
				for(int l=1;l<m;++l)
					swap(a[k][l],a[i][l]);
				swap(h[i],h[k]);
			}
			for(int j=1;j<=n;++j)
				if(a[j][i]&&j!=i)
					for(int l=1;l<=m;++l)
						a[j][l]^=a[k][l];
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j)
				printf("%d ",a[i][j]);
			puts("");
		}
		vector<int> b;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j)
				if(a[i][j])
					b.push_back(j);
			for(int j=0;j<b.size();++j)
				printf("%d ",b[j]);
			puts("");
			if(b.size()){
				ans*=solve(b);
				b.clear();
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
