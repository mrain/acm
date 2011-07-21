#include<cstdio>
typedef long long ll;
int ans,n,m;
struct int128
{
	ll high,low;
	int128(){}
	int128(ll _x,ll _y):high(_x),low(_y){}
	inline bool operator ==(const int128 &x)
	{
		return high==x.high&&low==x.low;
	}
	inline bool operator !=(const int128 &x)
	{
		return high!=x.high||low!=x.low;
	}
	inline int128 operator ^(const int128 &x)
	{
		return int128(high^x.high,low^x.low);
	}
	inline int128 operator &(const int128 &x)
	{
		return int128(high&x.high,low&x.low);
	}
	inline int128 operator |(const int128 &x)
	{
		return int128(high|x.high,low|x.low);
	}
}a[131],g[131],right[131];
inline void add(int x,int y)
{
	g[x]=g[x]|a[y];
}
void search(int128 now,int128 dai,int u)
{
	//printf("%lld %lld %d\n",now.low,dai.low,u);
	if(ans>1000)return;
	/*
	for(int i=1;i<=n;++i)
		if((a[i]&dai)==a[i]&&(g[i]&now)!=now)
			dai=dai^a[i];
	*/
	if(now==dai)
	{
		++ans;
		//printf("%d\n",ans);
		return;
	}
	if(u>n)return;
	for(int i=1;i<u;++i)
		if((now&a[i])!=a[i]&&(dai&a[i])==a[i]&&((right[i]&dai)==(right[i]&dai&g[i])))
			return;
	/*
	for(int i=u;i<=n;++i)
		if((now&g[i])==now&&(dai&a[i])!=a[i])
			return;*/
	/*
	for(int i=u;i<=n;++i)
		if((dai&a[i])!=a[i]&&(g[i]&dai)==dai)
		{
			puts("3");
			return;
		}
	*/
	for(int i=u;i<=n&&ans<=1000;++i)
		if((dai&a[i])==a[i])
			search(now|a[i],dai&g[i],i+1);
}
int main()
{
	for(int i=1;i<=128;++i)
		if(i<=64)
			a[i]=int128(0,1LL<<i-1);
		else
			a[i]=int128(1LL<<i-65,0);
	while(scanf("%d%d",&n,&m)==2)
	{
		for(int i=1;i<=n;++i)g[i]=a[i];
		right[n]=a[n];
		for(int i=n-1;i;--i)
			right[i]=a[i]|right[i+1];
		for(int i=1;i<=m;++i)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,y),add(y,x);
		}
		int128 now=int128(0,0);
		for(int i=1;i<=n;++i)
			now=now|a[i];
		ans=0;
		search(int128(0,0),now,1);
		if(ans>1000)puts("Too many maximal sets of friends.");
		else printf("%d\n",ans);
	}
	return 0;
}
