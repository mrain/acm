#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define M 700003
int rank[M],sa[M],X[M],Y[M],high[M],init[M];
int buc[M];
void calhigh(int n){
	register int i,j,k=0;
	for(i=1;i<=n;++i)rank[sa[i]]=i;
	for(i=0;i<n;high[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];init[i+k]==init[j+k];k++);
}
inline bool cmp(int *r,int a,int b,int l){
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
void suffix(int n,int m=128){
	register int i,l,p,*x=X,*y=Y;
	for(i=0;i<m;++i)buc[i]=0;
	for(i=0;i<n;++i)buc[x[i]=init[i]]++;
	for(i=1;i<m;++i)buc[i]+=buc[i-1];
	for(i=n-1;i>=0;--i)sa[--buc[x[i]]]=i;
	for(l=1,p=1;p<n;m=p,l*=2){
		p=0;
		for(i=n-l;i<n;++i)y[p++]=i;
		for(i=0;i<n;++i)if(sa[i]>=l)y[p++]=sa[i]-l;
		for(i=0;i<m;++i)buc[i]=0;
		for(i=0;i<n;++i)buc[x[y[i]]]++;
		for(i=1;i<m;++i)buc[i]+=buc[i-1];
		for(i=n-1;i>=0;--i)sa[--buc[x[y[i]]]]=y[i];
		for(swap(x,y),x[sa[0]]=0,i=1,p=1;i<n;++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],l)?p-1:p++;
	}
	calhigh(n-1);
}
int Log[M];
int best[21][M];
void initRMQ(int n){
	for(int i=1;i<=n;++i)best[0][i]=high[i];
	for(int i=1;i<=Log[n];++i)
		for(int j=1;j+(1<<i)-1<=n;++j)
			best[i][j]=min(best[i-1][j],best[i-1][j+(1<<i>>1)]);
}
inline int lcp(int a,int b){
	a=rank[a],b=rank[b];
	if(a>b)swap(a,b);
	a++;
	int t=Log[b-a+1];
	return min(best[t][a],best[t][b-(1<<t)+1]);
}
inline int llcp(int len,int a,int b){
	b=len-b-1;
	b+=len+1;
	//printf("%d %d\n",a,b);
	return lcp(a,b);
}
char s[M];
int l[M];
inline int calc(int l,int r){
	register int t=Log[r-l+1];
	return min(best[t][l],best[t][r-(1<<t)+1]);
}
inline int get(int l,int r,int v){
	if(calc(l,r)>v)return r+1;
	int rr=r;
	while(l!=r){
		register int mid=(l+r+1)>>1;
		if(calc(mid,rr)<=v)l=mid;
		else r=mid-1;
	}
	return l;
}
int main(){
	Log[0]=-1;
	for(int i=1;i<M;++i)Log[i]=(i&(i-1))?Log[i-1]:Log[i-1]+1;
	
	int _;
	for(scanf("%d",&_);_--;){
		scanf("%s",s);
		int len=strlen(s);
		//printf("%d\n", len);
		for(int i=0;i<len;++i)init[i]=s[i];
		init[len]=int('$');
		for(int i=0;len-1-i>i;++i)swap(s[i],s[len-1-i]);
		//printf("%s\n",s);
		for(int i=0;i<len;++i)init[len+i+1]=s[i];
		int n=len+len+1;
		init[n]=0;
		suffix(n+1,256);
		initRMQ(n);
		for(int i=0;i<len;++i)
			if(i!=len-1)l[i]=llcp(len,i+1,i);
			else l[i]=0;
		//for(int i=0;i<len;++i)printf("%d ",l[i]);
		//puts("");
		for(int i=1;i<=len;++i)best[0][i]=l[i-1];
		for(int i=1;i<=Log[len];++i)
			for(int j=1;j+(1<<i)-1<=len;++j)
				best[i][j]=min(best[i-1][j],best[i-1][j+(1<<i>>1)]);
		int ans=0;
		for(int i=0;i<len;++i){
			if(l[i]<2)continue;
			int x=get(i+1,l[i]/2+i,i+1);
			if(x>i+l[i]/2)continue;
			ans=max(ans,4*(x-(i+1)+1));
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
