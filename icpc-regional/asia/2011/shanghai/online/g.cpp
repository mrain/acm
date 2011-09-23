#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL(x) ((x)<<1)
#define RR(x) (((x)<<1)|1)
using namespace std;
typedef long long ll;
int n;
ll a[100003];
struct node{
	ll v[9];
	int d,len;
};
ll mysqrt(ll x){
	ll l=0,r=3037000499LL;
	while(l!=r){
		ll mid=(l+r+1)>>1;
		if(mid*mid<=x)l=mid;
		else r=mid-1;
	}
	return l;
}
node T[800003];
void push(int u){
	int v=T[u].d;
	v=min(v,7);
	for(int i=0;i<8;++i){
		if (i + v < 8) {
			T[LL(u)].v[i]=T[LL(u)].v[i+v];
			T[RR(u)].v[i]=T[RR(u)].v[i+v];
		} else {
			T[LL(u)].v[i]=T[LL(u)].len;
			T[RR(u)].v[i]=T[RR(u)].len;
		}
	}
	T[LL(u)].d+=v;
	T[RR(u)].d+=v;
	T[u].d=0;
}
void calc(int u){
	T[u].d = 0;
	T[u].len=T[LL(u)].len+T[RR(u)].len;
	T[u].v[0]=T[LL(u)].v[0]+T[RR(u)].v[0];
	T[u].v[1]=T[LL(u)].v[1]+T[RR(u)].v[1];
	T[u].v[2]=T[LL(u)].v[2]+T[RR(u)].v[2];
	T[u].v[3]=T[LL(u)].v[3]+T[RR(u)].v[3];
	T[u].v[4]=T[LL(u)].v[4]+T[RR(u)].v[4];
	T[u].v[5]=T[LL(u)].v[5]+T[RR(u)].v[5];
	T[u].v[6]=T[LL(u)].v[6]+T[RR(u)].v[6];
	T[u].v[7]=T[LL(u)].v[7]+T[RR(u)].v[7];
}
void initTree(int u,int l,int r){
	if(l==r){
		T[u].d=0;
		T[u].v[0]=a[l];
		T[u].len=1;
		for(int i=1;i<8;++i)
			T[u].v[i]=mysqrt(T[u].v[i-1]);
		return;
	}
	initTree(LL(u),l,(l+r)>>1);
	initTree(RR(u),((l+r)>>1)+1,r);
	calc(u);
}
void update(int u,int l,int r,int ll,int rr){
	if (ll > r) return;
	if (rr < l) return;
	if(ll<=l&&rr>=r){
		++T[u].d;
		T[u].v[0]=T[u].v[1];
		T[u].v[1]=T[u].v[2];
		T[u].v[2]=T[u].v[3];
		T[u].v[3]=T[u].v[4];
		T[u].v[4]=T[u].v[5];
		T[u].v[5]=T[u].v[6];
		T[u].v[6]=T[u].v[7];
		T[u].v[7]=T[u].len;
		return;
	}
	if(T[u].d)push(u);
	int mid=(l+r)>>1;
	update(LL(u),l,mid,ll,rr);
	update(RR(u),mid+1,r,ll,rr);
	calc(u);
}
ll query(int u,int l,int r,int ll,int rr){
	if (ll > r) return 0LL;
	if (rr < l) return 0LL;
	if(ll<=l&&rr>=r)
		return T[u].v[0];
	if(T[u].d)push(u);
	int mid=(l+r)>>1;
	return query(LL(u),l,mid,ll,rr)+query(RR(u),mid+1,r,ll,rr);
}
int main(){
	int cas=0;
	while(scanf("%d",&n)==1){
		for(int i=1;i<=n;++i)scanf("%lld",&a[i]);
		initTree(1,1,n);
		int m;
		scanf("%d",&m);
		printf("Case #%d:\n",++cas);
		for(int i=1;i<=m;++i){
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			if(!x)update(1,1,n,y,z);
			else printf("%lld\n",query(1,1,n,y,z));
		}
		puts("");
	}
	return 0;
}

