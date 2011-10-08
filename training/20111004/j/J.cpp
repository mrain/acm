#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL(x) (x<<1)
#define RR(x) (x<<1|1)
using namespace std;
int n,m,num,l;
struct rect{
	int x1,y1,x2,y2;
	rect(){}
	void read(){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
	}
	void inverse(){
		swap(x1,y1);
		swap(x2,y2);
	}
};
rect a[100003],b[100003];
map<int,int> h;

struct st{
	int v,x1,x2,d;
	st(){}
	st(int v,int x1,int x2,int d):v(v),x1(x1),x2(x2),d(d){}
	bool operator <(const st &a)const{
		return v<a.v;
	}
};
st Q[200003];

int length[200003];

struct node{
	int minv,minc,d;
	node(){}
	node operator +(const node &a){
		node ret; ret.d=0;
		ret.minv=min(minv,a.minv);
		ret.minc=0;
		if(minv==ret.minv)ret.minc+=minc;
		if(a.minv==ret.minv)ret.minc+=a.minc;
		return ret;
	}
};

node T[800010];

void Build(int u,int l,int r){
	T[u].d=0;
	if(l==r){
		T[u].minv=0;
		T[u].minc=length[l];
		return;
	}
	int mid=l+r>>1;
	Build(LL(u),l,mid);
	Build(RR(u),mid+1,r);
	T[u]=T[LL(u)]+T[RR(u)];
}

void push(int u){
	T[LL(u)].minv+=T[u].d;
	T[LL(u)].d+=T[u].d;
	T[RR(u)].minv+=T[u].d;
	T[RR(u)].d+=T[u].d;
	T[u].d=0;
}

void insert(int u,int l,int r,int ll,int rr,int v){
	if(ll>r||rr<l)return;
	if(T[u].d)push(u);
	if(ll<=l&&r<=rr){
		T[u].minv+=v;
		T[u].d += v;
		return;
	}
	int mid=l+r>>1;
	insert(LL(u),l,mid,ll,rr,v);
	insert(RR(u),mid+1,r,ll,rr,v);
	T[u]=T[LL(u)]+T[RR(u)];
}

int getLen(){
	if(T[1].minv==0)return T[1].minc;
	else return 0;
}

long long solve(int p,int q){
	h.clear();
	if(q<l)return 0;
//	puts("");
	for(int i=1;i<=num;++i){
		b[i]=a[i];
		b[i].x1 -= l - 1;
		b[i].x2+=1;
		if(b[i].x2 > q-l+2)b[i].x2=q-l+2;
		if(b[i].x1 > q-l+2)b[i].x1=q-l+2;
		if (b[i].x1 < 1) b[i].x1 = 1;
		if (b[i].x2 < 1) b[i].x2 = 1;
		//b[i].x2 ++;
		h[b[i].x1]=0;
		h[b[i].x2]=0;
	}
	h[1] = 0;
	h[q-l+2]=0;
	int cnt=0,lastv=-1;
	for(map<int,int>::iterator it=h.begin();it!=h.end();++it){
		if(lastv!=-1)length[cnt]=it->first-lastv;
		lastv=it->first;
		it->second=++cnt;
	}
	int tot=cnt-1;
	//cout << length[1] << ' ' << length[2] << endl;
	
	
	Build(1,1,tot);
	for(int i=1;i<=num;++i){
		//printf("A %d %d\n", b[i].x1, b[i].x2);
		b[i].x1=h[b[i].x1];
		b[i].x2=h[b[i].x2] - 1;
		//printf("B %d %d\n", b[i].x1, b[i].x2);
	}
	
	cnt=0;
	for(int i=1;i<=num;++i){
		if(b[i].x1 > b[i].x2) continue;
		Q[++cnt]=st(b[i].y1,b[i].x1,b[i].x2,1);
		//printf("A %d %d %d\n", b[i].y1, b[i].x1, b[i].x2);
		Q[++cnt]=st(b[i].y2+1,b[i].x1,b[i].x2,-1);
		//printf("B %d %d %d\n", b[i].y2 + 1, b[i].x1, b[i].x2);
	}
	
	stable_sort(Q+1,Q+cnt+1);
	
	long long ret=0;
	int last=1;
	for(int i=1;i<=cnt;++i){
		ret+=1LL*(Q[i].v-last)*getLen();
		insert(1,1,tot,Q[i].x1,Q[i].x2,Q[i].d);
		last=Q[i].v;
	}
	ret+=1LL*(p-last+1)*getLen();
	return ret;
}

int main(){
	while(scanf("%d%d%d%d",&n,&m,&num,&l)==4){
		for(int i=1;i<=num;++i)
			a[i].read();
			
		long long ans=solve(m,n);
		for(int i=1;i<=num;++i)
			a[i].inverse();
		if (l > 1) ans+=solve(n,m);
		cout<<ans<<endl;
	}
	return 0;
}

