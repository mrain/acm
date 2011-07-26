#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (200)

double f[maxn][maxn],g[maxn][maxn];
bool l[maxn],b[maxn];
int n,m,L,B;

const double trans=1./6.;

int main() {
	while (scanf("%d%d%d%d",&n,&m,&L,&B)==4&&(n+m+L+B)) {
		memset(f,0,sizeof(f)); memset(g,0,sizeof(g));
		memset(l,0,sizeof(l)); memset(b,0,sizeof(b));
		
		for (int i=0;i<L;i++) {
			int x; scanf("%d",&x);
			l[x]=true;
		}
		
		for (int i=0;i<B;i++) {
			int x; scanf("%d",&x);
			b[x]=true;
		}
		
		double ans=0.;
		f[0][0]=1.;
		
		for (int i=0;i<=m;i++) {
			ans+=f[i][n];
			
			for (int j=0;j<n;j++) if (f[i][j]>0.) {
				for (int k=1;k<=6;k++) {
					int x=j+k;
					if (x>n) x=n+n-j-k;
					
					g[i][x]+=trans*f[i][j];
				}
			}
			
			for (int j=0;j<=n;j++) if (g[i][j]>0.) {
				if (l[j]) {
					f[i+2][j]+=g[i][j]; continue;
				}
				
				if (b[j]) {
					f[i+1][0]+=g[i][j]; continue;
				}
				
				f[i+1][j]+=g[i][j];
			}
		}
		
		printf("%.10f\n",ans);
	}
}
