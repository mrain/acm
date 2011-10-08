#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL(x) (x<<1)
#define RR(x) (x<<1|1)
using namespace std;

int n,m;
char col[60003];

struct node{
	int l,r,cnt;
	node(){}
	node operator +(const node &a){
		if((*this).l==0)return a;
		if(a.l==0)return *this;
		node ret;
		ret.l=l;
		ret.r=a.r;
		ret.cnt=cnt+a.cnt;
		if(r==a.l-1){
			if(a.r>a.l&&col[r]=='w'&&col[a.l]=='b'&&col[a.l+1]=='w')
				++ret.cnt;
			if(r>l&&col[r-1]=='w'&&col[r]=='b'&&col[a.l]=='w')
				++ret.cnt;
		}
		return ret;
	}
};
node T[300003],Null;

void makeTree(int u,int l,int r){
	if(l==r){
		T[u].l=l;
		T[u].r=r;
		T[u].cnt=0;
		return;
	}
	int mid=l+r>>1;
	makeTree(LL(u),l,mid);
	makeTree(RR(u),mid+1,r);
	T[u]=T[LL(u)]+T[RR(u)];
}

void updateTree(int u,int x){
	if(T[u].l==T[u].r)return;
	int mid=T[u].l+T[u].r>>1;
	if(x<=mid)updateTree(LL(u),x);
	if(x>mid)updateTree(RR(u),x);
	T[u]=T[LL(u)]+T[RR(u)];
}

void changeTree(int u,char ch){
	col[u]=ch;
	updateTree(1,u);
}

node askTree(int u,int l,int r){
	if(l>T[u].r||r<T[u].l)return Null;
	if(l<=T[u].l&&T[u].r<=r)return T[u];
	int mid=l+r>>1;
	return askTree(LL(u),l,r)+askTree(RR(u),l,r);
}

int main(){
	Null.l=Null.r=0;

	int _,cas=0;
	for(scanf("%d",&_);_--;){
		scanf("%d%d",&n,&m);
		scanf("%s",col+1);
		
		makeTree(1,1,n);
		
		printf("Case %d:\n",++cas);
		for(int i=0;i<m;++i){
			int cmd;
			scanf("%d",&cmd);
			
			if(cmd==0){
				int l,r;
				scanf("%d%d",&l,&r);
				printf("%d\n",askTree(1,l+1,r+1).cnt);
			}
			if(cmd==1){
				int k;char t[4];
				scanf("%d%s",&k,t);
				changeTree(k+1,t[0]);
			}
		}
	}
	return 0;
}
