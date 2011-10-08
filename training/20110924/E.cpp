#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL(x) (x<<1)
#define RR(x) ((x<<1)|1)
using namespace std;
const int N=100003;
typedef long double ld;
int n,m;
ld sum1[N],sum2[N];

struct node{
	int l,r;
	ld v,vi,vii,d;
	node(){}
	node operator +(const node &a){
		node ret;
		ret.v=v+a.v;
		ret.vi=vi+a.vi;
		ret.vii=vii+a.vii;
		ret.d=0;
		ret.l=l;
		ret.r=a.r;
		return ret;
	}
};
node T[N*5];

void initTree(int u,int l,int r){
	if(l==r){
		T[u].v=T[u].vi=T[u].vii=T[u].d=0;
		T[u].l=T[u].r=r;
		return;
	}
	int mid=l+r>>1;
	initTree(LL(u),l,mid);
	initTree(RR(u),mid+1,r);
	T[u]=T[LL(u)]+T[RR(u)];
}

void update(int u,int v){
	T[u].d+=v;
	T[u].v+=ld(1.0)*(T[u].r-T[u].l+1)*v;
	T[u].vi+=(sum1[T[u].r]-sum1[T[u].l-1])*v;
	T[u].vii+=(sum2[T[u].r]-sum2[T[u].l-1])*v;
}

void push(int u){
	update(LL(u),T[u].d);
	update(RR(u),T[u].d);
	T[u].d=0;
}

void updTree(int u,int l,int r,int v){
	if(l>T[u].r||r<T[u].l)return;
	if(l<=T[u].l&&T[u].r<=r){
		update(u,v);
		return;
	}
	if(T[u].d)push(u);
	updTree(LL(u),l,r,v);
	updTree(RR(u),l,r,v);
	T[u]=T[LL(u)]+T[RR(u)];
}

void queryTree(int u,int l,int r,ld &x,ld &y,ld &z){
	if(l>T[u].r||r<T[u].l){
		x=y=z=0;
		return;
	}
	if(l<=T[u].l&&T[u].r<=r){
		x=T[u].v;
		y=T[u].vi;
		z=T[u].vii;
		return;
	}
	if(T[u].d)push(u);
	ld x1,y1,z1,x2,y2,z2;
	queryTree(LL(u),l,r,x1,y1,z1);
	queryTree(RR(u),l,r,x2,y2,z2);
	x=x1+x2;
	y=y1+y2;
	z=z1+z2;
}

ld query(int l,int r){
	ld x,y,z;
	queryTree(1,l,r,x,y,z);
	//cout << l << ' ' << r << ' ' << z << ' ' << y << ' ' << x << endl;
	//ld ret=-z+(l+r-1)*y-(l*r-r)*x;
	ld ret = -z + (ld)(l + r) * y - (ld)(l - 1) * (r + 1) * x;
	//cout << ret << endl;
	/*if(l==r)return ret;
	else */return ret*2.0/(r-l+2)/(r-l+1);
}

int main(){
	cout.setf(ios::fixed);
	cout.precision(8);
	scanf("%d%d",&n,&m);
	--n;
	for(int i=1;i<=n;++i)sum1[i]=sum1[i-1]+i;
	for(int i=1;i<=n;++i)sum2[i]=sum2[i-1]+1.0*i*i;
	initTree(1,1,n);
	for(int i=1;i<=m;++i){
		char s[11];
		int x,y,z;
		scanf("%s%d%d",s,&x,&y);
		if(s[0]=='c'){
			scanf("%d",&z);
			updTree(1,x,y-1,z);
		}
		else
			cout << query(x,y-1) << endl;
	}
	return 0;
}
