#include<cstdio>
#include<cstring>
#include<algorithm>
#define lowbit(x) ((x)&-(x))
using namespace std;
int n,m,p[11];
int a[1027],cnt[1027],inte[11][1027],bonus[11][11],f[11][1027];
bool g[11][1027];
int main(){
	for(int i=1;i<1027;++i)
		cnt[i]=1+cnt[i-lowbit(i)];
	
	while(scanf("%d%d",&n,&m)==2&&(n||m)){
		for(int i=1;i<=m;++i)
			scanf("%d",p+i);
			
		memset(inte,0,sizeof(inte));
		memset(a,0,sizeof(a));
		
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j){
				int x;
				scanf("%d",&x);
				inte[j][1<<i-1]=x;
			}
			
		for(int i=1;i<=m;++i)
			for(int j=1;j<(1<<n);++j)
				inte[i][j]=inte[i][j-lowbit(j)]+inte[i][lowbit(j)];
		
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				scanf("%d",bonus[i]+j);
				
		for(int i=1;i<(1<<n);++i)
			for(int j=1;j<n;++j)
				if(i&(1<<j-1))
					for(int k=j+1;k<=n;++k)
						if(i&(1<<k-1))
							a[i]+=bonus[j][k];
		
		memset(g,0,sizeof(g));
		g[0][(1<<n)-1]=1;
		for(int i=0;i<m;++i)
			for(int j=0;j<(1<<n);++j)
				if(g[i][j]){
					for(int k=j;;k=(k-1)&j){
						if(g[i+1][k])
							f[i+1][k]=max(f[i+1][k],f[i][j]+a[k]+inte[i+1][k]-cnt[k]*p[i+1]);
						else{
							f[i+1][k]=f[i][j]+a[k]+inte[i+1][k]-cnt[k]*p[i+1];
							g[i+1][k]=1;
						}
						if(k==0)break;
					}
				}
		
		int ans=-1;
		for(int j=0;j<(1<<n);++j)
			if(g[m][j])
				ans=max(ans,f[m][j]);
		if(ans>0)printf("%d\n",ans);
		else puts("STAY HOME");
	}
	return 0;
}
