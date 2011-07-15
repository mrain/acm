#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;

#define maxn (110)

const int mod=10000,bound=50;

int g[maxn][maxn],tg[maxn][maxn];
int f[maxn],tf[maxn],a[maxn],b[maxn];
int n,t;

int main(){
	while (scanf("%d",&n)==1&&n) {
		
		memset(g,0,sizeof(g));
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		for (int i=1;i<=n;i++) scanf("%d",&b[i]);
		scanf("%d",&t);
		
		for (int i=1;i<=n;i++) f[i]=a[i];
		for (int i=1;i<n;i++) g[i][i+1]=1;
		for (int i=1;i<=n;i++) g[n][i]=b[n-i+1];
		
		if (t<n) {
			printf("%d\n",a[t+1]); continue;
		}
		
		int x=t-n+1;
		while (x) {
			if (x&1) {
				memset(tf,0,sizeof(tf));
				
				for (int i=1;i<=n;i++) 
					for (int j=1;j<=n;j++)
						(tf[i]+=f[j]*g[i][j])%=mod;
						
				memcpy(f,tf,sizeof(f));
			}
			
			x/=2;
			
			memset(tg,0,sizeof(tg));
			for (int k=1;k<=n;k++)
				for (int i=1;i<=n;i++)
					for (int j=1;j<=n;j++)
						(tg[i][j]+=g[i][k]*g[k][j])%=mod;
			memcpy(g,tg,sizeof(g));
		}	
		
		printf("%d\n",f[n]);
	}

	return 0;
}

