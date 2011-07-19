#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (210000)

struct ele{
	int num,cov;
}f[maxn*8];
int g[maxn],org[maxn];
int m,n;

void build(int x,int st,int ed) {
	if (st==ed) {
		f[x].num=g[st]; return ;	
	}
	
	int mid=(st+ed)/2;
	
	build(x+x,st,mid),build(x+x+1,mid+1,ed);
	
	f[x].num=min(f[x+x].num,f[x+x+1].num);
}

void add(int x,int st,int ed,int p,int q,int v) {
	if (st==p&&ed==q) {
		f[x].cov+=v; return ;
	}
	
	if (f[x].cov) {
		f[x+x].cov+=f[x].cov,f[x+x+1].cov+=f[x].cov;
		f[x].cov=0;
	}
	
	int mid=(st+ed)/2;
	
	if (q<=mid) {
		add(x+x,st,mid,p,q,v);
	}
	else {
		if (p>mid) {
			add(x+x+1,mid+1,ed,p,q,v);
		}
		else {
			add(x+x,st,mid,p,mid,v); add(x+x+1,mid+1,ed,mid+1,q,v);
		}
	} 
	
	f[x].num=min(f[x+x].num+f[x+x].cov,f[x+x+1].num+f[x+x+1].cov);
}

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&org[i]); org[i]=n-org[i]+1; 
		g[org[i]]++;
	}
	
	for (int i=1;i<=n;i++) g[i]+=g[i-1];
	for (int i=1;i<=n;i++) g[i]-=i;
	
	build(1,1,n);
	
	if (f[1].num+f[1].cov<0) puts("NIE");
	else puts("TAK");
	
	scanf("%d",&m);
	
	for (int i=1;i<=m;i++) {
		int a,x; scanf("%d%d",&a,&x);
		x=n-x+1; int y=org[a];
		
		if (x!=y) {
			if (x<y) add(1,1,n,x,y-1,1);  
			else add(1,1,n,y,x-1,-1);
		}
		
		org[a]=x;
		
		if (f[1].num+f[1].cov<0) puts("NIE");
		else puts("TAK");
	}

	return 0;
}
