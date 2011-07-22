#include<cstdio>
#include<algorithm>
#include <iostream>
#define LL(x) ((x)<<1)
#define RR(x) (((x)<<1)|1)
using namespace std;
int n,m,I;
struct Tree
{
	int mi,ma,d;
	Tree(){}
	Tree operator +(const Tree &x)
	{
		Tree ret;
		ret.mi=min(mi,x.mi);
		ret.ma=max(ma,x.ma);
		ret.d=0;
		return ret;
	}
}T[1600003];
void Build(int u,int l,int r)
{
	if(l==r)
	{
		T[u].mi=T[u].ma=I;
		T[u].d=0;
		return;
	}
	int mid=(l+r)>>1;
	Build(LL(u),l,mid);
	Build(RR(u),mid+1,r);
	T[u]=T[LL(u)]+T[RR(u)];
}
inline void change(int u,int v)
{
	if(T[u].mi>0)T[u].mi+=v;
	if(T[u].ma>0)T[u].ma+=v;
}
inline void push(int u)
{
	if(T[u].ma>0&&T[u].d!=0)
	{
		T[LL(u)].d+=T[u].d;
		T[RR(u)].d+=T[u].d;
		change(LL(u),T[u].d);
		change(RR(u),T[u].d);
	}
	T[u].d=0;
}
int ask(int u,int l,int r,int ll,int rr)
{
	if(T[u].ma<1)return 0;
	if(l==ll&&r==rr)
	{
		//printf("%d %d %d %d\n",u,ll,rr,T[u].mi);
		return T[u].mi;
	}
	if(T[u].d)
		push(u);
	int mid=(l+r)>>1;
	if(rr<=mid)
		return ask(LL(u),l,mid,ll,rr);
	else if(ll>mid)
		return ask(RR(u),mid+1,r,ll,rr);
	else
	{
		int t1=ask(LL(u),l,mid,ll,mid);
		if(t1<1)return t1;
		int t2=ask(RR(u),mid+1,r,mid+1,rr);
		return min(t1,t2);
	}
}
void Update(int u,int l,int r,int ll,int rr,int v)
{
	if(T[u].ma<1)return;
	if(l==ll&&r==rr)
	{
		T[u].d=v;
		change(u,v);
		return;
	}
	if(T[u].d)
		push(u);
	int mid=(l+r)>>1;
	if(rr<=mid)
		Update(LL(u),l,mid,ll,rr,v);
	else if(ll>mid)
		Update(RR(u),mid+1,r,ll,rr,v);
	else
	{
		Update(LL(u),l,mid,ll,mid,v);
		Update(RR(u),mid+1,r,mid+1,rr,v);
	}
	T[u]=T[LL(u)]+T[RR(u)];
}
void Update2(int u,int l,int r,int ll,int rr,int v)
{
	if(T[u].ma<1||T[u].mi>=v)return;
	if(l==r)
	{
		if(T[u].mi>0)
			T[u].mi=max(T[u].mi,v);
		if(T[u].ma>0)
			T[u].ma=max(T[u].ma,v);
		return;
	}
	if(T[u].d)
		push(u);
	int mid=(l+r)>>1;
	if(rr<=mid)Update2(LL(u),l,mid,ll,rr,v);
	else if(ll>mid) Update2(RR(u),mid+1,r,ll,rr,v);
	else
	{
		Update2(LL(u),l,mid,ll,mid,v);
		Update2(RR(u),mid+1,r,mid+1,rr,v);
	}
	T[u]=T[LL(u)]+T[RR(u)];
}
int main()
{
	while(scanf("%d%d%d",&n,&m,&I)==3&&(n||m||I))
	{
		Build(1,1,n);
		int ans=0;
		for(;m--;)
		{
			int c,x,y,d;
			scanf("%d%d%d%d",&c,&x,&y,&d);
//			cout<<ask(1,1,n,1,1)<<endl;
			switch(c)
			{
				case 1:
				{
					if(ask(1,1,n,x,y)>0) {
						++ans;
						Update(1,1,n,x,y,-d);
					}
					break;
				}
				case 2:
				{
					Update(1,1,n,x,y,d);
					break;
				}
				case 3:
				{
					Update2(1,1,n,x,y,d);
					break;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
