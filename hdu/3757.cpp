#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

#define maxn (4005)

typedef long long LL;

struct ele{
	LL pos; 
	int ord;
}a[maxn],b[maxn];

LL f[2][maxn];
int m,n;

short r[maxn*maxn/2];
short ans[maxn],out[maxn];

const LL inf=1000000000000000ll;

inline int code(const int& i,const int& j) {
	return (i*i-i)/2+j;
}

inline void decode(const int& x,int& i,int& j) {
	i=(int)sqrt(x*2); j=-(i*i-i)/2+x;
	
	if (j>i) {
		i++; j=-(i*i-i)/2+x;
	}
}

void init(LL& v) {
	int x; scanf("%d",&x);
	
	v=(LL)x;
}

bool operator<(ele a,ele b) {
	return a.pos<b.pos;
}

inline LL dist(const int& i,const int& j) {
	return a[i].pos < b[j].pos ? b[j].pos - a[i].pos : a[i].pos - b[j].pos ;
} 

void outit() {
	int x=n; ans[m+1]=n+1;
	
	for (int i=m;i>0;i--) {
		int tmp=r[code(x,i)];
		ans[i]=tmp;
		x=tmp-1; 
	}
	
	for (int i=1;i<=m;i++) 
		for (int k=ans[i];k<ans[i+1];k++) 
			out[a[k].ord]=b[i].ord;
	
	for (int i=1;i<n;i++) printf("%d ",out[i]); printf("%d\n",out[n]); 
} 

int main(){
	int T; scanf("%d",&T);
	
	while (T--) {
		scanf("%d",&n);
		for (int i=1;i<=n;i++) init(a[i].pos),a[i].ord=i;
		scanf("%d",&m);
		for (int i=1;i<=m;i++) init(b[i].pos),b[i].ord=i;
		
		sort(a+1,a+1+n); sort(b+1,b+1+m);
		
		int now=0;
		f[now][1]=dist(1,1),r[code(1,1)]=1;
		for (int t=2;t<=n;t++) {
			int to=now^1;
			
			for (int i=1;i<=t;i++) f[to][i]=inf,r[code(t,i)]=0;
			
			int ed=min(t-1,m);
			for (int i=1;i<t;i++) if (f[now][i]!=inf) {
				LL tmp=f[now][i]+dist(t,i);
				if (f[to][i]>tmp) f[to][i]=tmp,r[code(t,i)]=r[code(t-1,i)];
				
				if (i==m) continue;
				tmp=f[now][i]+dist(t,i+1);
				if (f[to][i+1]>tmp) f[to][i+1]=tmp,r[code(t,i+1)]=t; 
			}
			
			now=to;
		}
		
		cout << f[now][m] << endl ;
		outit();
	}

	return 0;
}
