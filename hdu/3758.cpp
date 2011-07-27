#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (21000)

const int bound=11000;

int fac[maxn],sum[maxn],p[maxn],a[maxn],b[maxn],now[maxn],rep[maxn];
int ans[maxn][2];
int c,m,n,t;

void ready() {
	for (int i=2;i<=bound;i++) if (!fac[i]) {
		p[++c]=i;
		for (int k=i;k<=bound;k+=i) fac[k]=c;
	}
}

void work() {
	memset(now,0,sizeof(now)); memset(rep,0,sizeof(rep)); memset(sum,0,sizeof(sum));
	
	scanf("%d%d",&m,&n);
	for (int i=1;i<=m;i++) scanf("%d",&a[i]);
	for (int i=1;i<=m;i++) rep[a[i]]++;
	for (int i=1;i<=n;i++) scanf("%d",&b[i]);
	for (int i=1;i<=n;i++) rep[b[i]]--;
/*	
	memset(rep,0,sizeof(rep));
	rep[3]=1000;
*/
	for (int i=2;i<=bound;i++) {
		int k=i;
		
		while (fac[k]) {
			sum[fac[k]]++; k/=p[fac[k]];
		}
		
		if (rep[i]!=0) {
			//printf("%d -> %d\n",i,rep[i]);
		
			for (int j=1;j<=c;j++) {
				if (!sum[j]) break;
				now[j]+=rep[i]*sum[j];
			}
		} 
	}
/*	
	for (int i=1;i<=c;i++) {
		if (now[i]) printf("%d: %d\n",p[i],now[i]);
	}
*/	
	bool flag=true;
	for (int i=1;i<=c;i++) {
		if (now[i]<0) {
			flag=false; break;
		}
	}
	
	if (!flag) {
		puts("-1"); return ;
	}
	
	t=0;
	for (int i=bound;i>1;i--) {
	
		int x=1000000000;
		for (int j=1;j<=c;j++) {
			if (!sum[j]) break;
			
			if (sum[j]) x=min(x,now[j]/sum[j]);
		}
		
		if (x>0) {
			t++; ans[t][0]=i,ans[t][1]=x;
			
			for (int j=1;j<=c;j++) {
				if (!sum[j]) break;
				now[j]-=x*sum[j];
			}
		}
		
		int k=i;
		
		while (fac[k]) {
			sum[fac[k]]--; k/=p[fac[k]];
		}
	}
	
	printf("%d\n",t);
	for (int i=1;i<=t;i++) printf("%d %d\n",ans[i][0],ans[i][1]);
}

int main(){
	ready();
	
	int T; scanf("%d",&T);
	
	while (T--) work();

	return 0;
}
