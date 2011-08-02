#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int n,a[107],ra[107],now[3][23],best[3][23],times[7],ans;
bool cmp(int x,int y)
{
	if(a[x]!=a[y])
		return a[x]<a[y];
	else return x<y;
}
struct state
{
	int v,t;
	state(){}
	state(int v,int t):v(v),t(t){}
	bool operator <(const state &x)const
	{
		if(t!=x.t)return t<x.t;
		else return v<x.v;
	}
}p[17],q[17];
bool compare(int u)
{
	if(u>ans)return true;
	if(u<ans)return false;
	int fa1=0;
	for(int i=0;i<3;++i)
	{
		int tmp=0;
		for(int j=1;j<=now[i][0];++j)
			tmp+=a[now[i][j]],fa1+=tmp;
	}
	int fa2=0;
	for(int i=0;i<3;++i)
	{
		int tmp=0;
		for(int j=1;j<=best[i][0];++j)
			tmp+=a[best[i][j]],fa2+=tmp;
	}
	if(fa1<fa2)return true;
	if(fa1>fa2)return false;
	int cnt1=0;
	for(int i=0;i<3;++i)
	{
		int tmp=0;
		for(int j=1;j<=now[i][0];++j)
			tmp+=a[now[i][j]],p[++cnt1]=state(now[i][j],tmp);
	}
	stable_sort(p+1,p+cnt1+1);
	int cnt2=0;
	for(int i=0;i<3;++i)
	{
		int tmp=0;
		for(int j=1;j<=best[i][0];++j)
			tmp+=a[best[i][j]],q[++cnt2]=state(best[i][j],tmp);
	}
	stable_sort(q+1,q+cnt2+1);
	for(int i=1;i<=cnt1;++i)
		if(p[i].v!=q[i].v)
			return p[i].v<q[i].v;
	return false;
}
void search(int u)
{
	if(u==n) {
		if(compare(u))
		{
			ans=u;
			memcpy(best,now,sizeof(now));
		}
		return;
	}
	bool flag =false;
	++u;
	for(int i=0;i<3;++i)
		if(times[i]+a[ra[u]]<=300)
		{
			flag = true;
			now[i][++now[i][0]]=ra[u];
			times[i]+=a[ra[u]];
			search(u);
			times[i]-=a[ra[u]];
			--now[i][0];
		}
	if(!flag && compare(u))
	{
		ans=u;
		memcpy(best,now,sizeof(now));
	}
}
int main()
{
	int _,cas=0;
	for(scanf("%d",&_);_--;)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
		{
			ra[i]=i;
			scanf("%d",a+i);
		}
		ans=0;
		memset(now,0,sizeof(now));
		memset(times,0,sizeof(times));
		sort(ra+1,ra+n+1,cmp);
		search(0);
		printf("Data set %d:",++cas);
		int cnt2=0,fashi=0;
		for(int i=0;i<3;++i)
		{
			int tmp=0;
			for(int j=1;j<=best[i][0];++j)
				tmp+=a[best[i][j]],q[++cnt2]=state(best[i][j],tmp),fashi+=tmp;
		}
		stable_sort(q+1,q+cnt2+1);
		for(int i=1;i<=cnt2;++i)
			printf(" %c",'A'+q[i].v-1);
		printf(" %d %d\n",cnt2,fashi);
	}
	return 0;
}
