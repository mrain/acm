#include<cstdio>
#include<algorithm>
using namespace std;
const int MX=100003;
struct state
{
	int v,bb,be,eb,ee;
}a[MX];
int n,t;
long long f[MX][2],g[MX][2];
char ans[MX];
long long calc1()
{
	f[1][0]=1LL<<60;
	f[1][1]=a[1].v;
	f[2][0]=f[1][1]+a[1].ee;
	g[2][0]=1;
	f[2][1]=f[1][1]+a[1].eb;
	g[2][1]=1;
	f[2][0]+=a[2].v,f[2][1]+=a[2].v;
	for(int i=3;i<=n;++i)
	{
		if(f[i-1][0]+a[i-1].be<=f[i-1][1]+a[i-1].ee)
		{
			f[i][0]=f[i-1][0]+a[i-1].be;
			g[i][0]=0;
		}
		else
		{
			f[i][0]=f[i-1][1]+a[i-1].ee;
			g[i][0]=1;
		}
		if(f[i-1][0]+a[i-1].bb<=f[i-1][1]+a[i-1].eb)
		{
			f[i][1]=f[i-1][0]+a[i-1].bb;
			g[i][1]=0;
		}
		else
		{
			f[i][1]=f[i-1][1]+a[i-1].eb;
			g[i][1]=1;
		}
		f[i][0]+=a[i].v,f[i][1]+=a[i].v;
	}
	f[n][0]+=a[n].bb;
	f[n][1]+=a[n].eb;
	return min(f[n][0],f[n][1]);
}
void out1()
{
	int x=n,y;
	if(f[n][0]<=f[n][1])y=0;
	else y=1;
	for(;x;--x)
	{
		ans[x]=y?'F':'B';
		y=g[x][y];
	}
	for(int i=1;i<=n;++i)
		putchar(ans[i]);
	puts("");
}
long long ff[MX][2],gg[MX][2];
long long calc2()
{
	ff[1][0]=a[1].v;
	ff[1][1]=1LL<<60;
	ff[2][0]=ff[1][0]+a[1].be;
	gg[2][0]=0;
	ff[2][1]=ff[1][0]+a[1].bb;
	gg[2][1]=0;
	ff[2][0]+=a[2].v,ff[2][1]+=a[2].v;
	for(int i=3;i<=n;++i)
	{
		if(ff[i-1][0]+a[i-1].be<=ff[i-1][1]+a[i-1].ee)
		{
			ff[i][0]=ff[i-1][0]+a[i-1].be;
			gg[i][0]=0;
		}
		else
		{
			ff[i][0]=ff[i-1][1]+a[i-1].ee;
			gg[i][0]=1;
		}
		if(ff[i-1][0]+a[i-1].bb<=ff[i-1][1]+a[i-1].eb)
		{
			ff[i][1]=ff[i-1][0]+a[i-1].bb;
			gg[i][1]=0;
		}
		else
		{
			ff[i][1]=ff[i-1][1]+a[i-1].eb;
			gg[i][1]=1;
		}
		ff[i][0]+=a[i].v,ff[i][1]+=a[i].v;
	}
	ff[n][0]+=a[n].be;
	ff[n][1]+=a[n].ee;
	return min(ff[n][0],ff[n][1]);
}
void out2()
{
	int x=n,y;
	if(ff[n][0]<=ff[n][1])y=0;
	else y=1;
	for(;x;--x)
	{
		ans[x]=y?'F':'B';
		y=gg[x][y];
	}
	for(int i=1;i<=n;++i)
		putchar(ans[i]);
	puts("");
}
int main()
{
	int _;
	for(scanf("%d",&_);_--;)
	{
		scanf("%d%d",&n,&t);
		for(int i=1;i<=n;++i)
			scanf("%d%d%d%d%d",&a[i].v,&a[i].bb,&a[i].be,&a[i].eb,&a[i].ee);
		long long v1=calc1();
		long long v2=calc2();
		//printf("%lld\n",min(v1,v2));
		if(min(v1,v2)>t)
		{
			puts("IMPOSSIBLE");
			continue;
		}
		if(v1<=v2)
			out1();
		else
			out2();
	}
	return 0;
}
