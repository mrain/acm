#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int MOD=1000000007;
int f[1003][1003],g[1003][1003];
int main(){
	f[0][0]=1;
	for(int i=1;i<1003;++i)
		for(int j=1;j<=i;++j){
			f[i][j]=1LL*j*f[i-1][j]%MOD+f[i-1][j-1];
			if(f[i][j]>=MOD)f[i][j]-=MOD;
		}
	
	for(int i=1;i<1003;++i)
		for(int j=1;j<=i;++j){
			f[i][j]+=f[i][j-1];
			if(f[i][j]>=MOD)f[i][j]-=MOD;
		}
	
	int n,r,k,m;
	while(scanf("%d%d%d%d",&n,&r,&k,&m)==4){
		memset(g,0,sizeof(g));
		g[0][0]=1;
		for(int i=1;i<=n;++i){
			g[i][0]=1;
			for(int j=1;j<=i;++j){
				g[i][j]=g[i-1][j]+g[max(i-k,0)][j-1];
				if(g[i][j]>=MOD)g[i][j]-=MOD;
			}
		}
		cout<<1LL*g[n][r]*f[r][min(r,m)]%MOD<<endl;
	}
	return 0;
}
