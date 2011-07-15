#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (1100000)
#define maxm (maxn*6)

int r[maxm],rank[maxm],sa[maxm],wa[maxn],wb[maxn],wv[maxm],h[maxn],ws[maxm];
int st[10],mark[10];
char buf[maxn];
int N,n,bound;

inline int convert(const char& x) {
	switch (x) {
		case 'A' : return 1;
		case 'C' : return 2;
		case 'G' : return 3;
		case 'T' : return 4;
		default 
 	}
}

void init(){
	scanf("%d\n",&N);
	
	bound=n=0;
	for (int i=1;i<=N;i++) {
		gets(buf); st[i]=now;
		
		int len=0;
		
		for (int j=0;buf[j];j++,len++) r[n++]=convert(buf[j]);
		
		r[n++]=0,bound=max(bound,len);
	}
}	

inline bool cmp(int *r,int a,int b,int l) {
	return r[a]==r[b]&&r[a+l]==r[b+l];
}

void da(int m) {
	int *x=wa,*y=wb,*t;
	int i,j,p;

	for (i=0;i<m;i++) ws[i]=0;
	for (i=0;i<n;i++) ws[x[i]=r[i]]++;
	for (i=0;i<m;i++) ws[i]+=ws[i-1];
	for (i=n-1;i>=0;i--) sa[--ws[x[i]]]=i;
	
	for (j=1,p=1;p<n;j*=2,m=p) {
		for (p=0,i=n-j;i<n;i++) y[p++]=i;
		for (i=0;i<n;i++) if (sa[i]>=j) y[p++]=sa[i]-j;
		for (i=0;i<n;i++) wv[i]=x[y[i]];
		for (i=0;i<m;i++) ws[i]=0;
		for (i=0;i<n;i++) ws[wv[i]]++;
		for (i=0;i<m;i++) ws[i]+=ws[i-1];
		for (i=n-1;i>=0;i--) sa[--ws[wv[i]]]=y[i];
		for (t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++) x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}

void ch() {
	int i,j,k=0;
	
	for (i=1;i<=n;i++) rank[sa[i]]=i;
	for (i=0;i<n;h[rank[i++]]=k)
		for (k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
}

bool check(int x) {
	memset(mark,0,sizeof(mark));
	int cnt=0;
	
	for (int i=2;i<=n;i++) {
		if (h[i]<x) {
			
		}
	}
}

void work(){
	da(5); n--; ch();
	
	int l=1,r=bound,ans=0;
	
	while (l<=r) {
		int mid=(l+r)/2;
		
		if (check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	
	
	printf("%d\n",ans);
}

int main(){
	int T; scanf("%d",&T);
	
	for (int t=1;t<=T;t++) {
		init(); work();
	}

	return 0;
}
