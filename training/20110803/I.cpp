#include<cstdio>
#include<cmath>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const double eps=1e-7;
int m,n,k,vm,vn,vk;
int bomber[301][2],plane[301][2],mis[301],lk[303];
double lisan[1003];
vector<int> g[301];
bool use[1003],vis[303];
struct inter
{
	int x,y,h;
	int isb;
	inter(){}
	bool operator <(const inter &a)const{
		return h<a.h;
	}
}a[301];
int calc(int cnt,double x)
{
	return lower_bound(lisan+1,lisan+cnt+1,x)-lisan;
}
bool find(int x)
{
	for(int i=0;i<g[x].size();++i)
	{
		int y=g[x][i];
		if(vis[y])continue;
		vis[y]=1;
		if(!lk[y]||find(lk[y]))
		{
			vis[y]=0;
			lk[y]=x;
			return 1;
		}
	}
	return 0;
}
int main()
{
	int _,cas=0;
	for(scanf("%d",&_);_--;)
	{
		++cas;
		scanf("%d%d%d",&m,&n,&k);
		scanf("%d%d%d",&vm,&vn,&vk);
		for(int i=1;i<=m;++i)
			scanf("%d%d",bomber[i],bomber[i]+1);
		for(int i=1;i<=n;++i)
			scanf("%d%d",plane[i],plane[i]+1);
		for(int i=1;i<=k;++i)
			scanf("%d",mis+i);
		for(int i=1;i<=k;++i)
			g[i].clear();
		for(int i=1;i<=k;++i)
		{
			int cnt=0;
			for(int j=1;j<=m;++j)
			{
				if(bomber[j][0]>mis[i])continue;
				//if(bomber[j][1]/double(vk)*vm>mis[i]+eps)continue;
				double l=(mis[i]-bomber[j][0]-1)/double(vm)-bomber[j][1]/double(vk);
				l=max(l,0.);
				double r=(mis[i]-bomber[j][0])/double(vm)-bomber[j][1]/double(vk);
				if(r<0)continue;
				//printf("%.4f %.4f\n",l,r);
				if(r==l)l-=eps,r+=eps;
				lisan[++cnt]=l,lisan[++cnt]=r;
			}
			for(int j=1;j<=n;++j)
			{
				if(plane[j][0]>mis[i])continue;
				//if(plane[j][1]/double(vk)*vn>mis[i]+eps)continue;
				double l=(mis[i]-plane[j][0]-1)/double(vn)-plane[j][1]/double(vk);
				l=max(l,0.);
				double r=(mis[i]-plane[j][0])/double(vn)-plane[j][1]/double(vk);
				if(r<0)continue;
				//printf("%.4f %.4f\n",l,r);
				if(r==l)l-=eps,r+=eps;
				lisan[++cnt]=l,lisan[++cnt]=r;
			}
			//puts("");
			stable_sort(lisan+1,lisan+cnt+1);
			int ccnt=0;
			for(int j=1;j<=cnt;++j)
				if(j==1||lisan[j]!=lisan[j-1])
					lisan[++ccnt]=lisan[j];
			cnt=ccnt;
			ccnt=0;
			for(int j=1;j<=m;++j)
			{
				if(bomber[j][0]>mis[i])continue;
				//if(bomber[j][1]/double(vk)*vm>mis[i]+eps)continue;
				double l=(mis[i]-bomber[j][0]-1)/double(vm)-bomber[j][1]/double(vk);
				l=max(l,0.);
				double r=(mis[i]-bomber[j][0])/double(vm)-bomber[j][1]/double(vk);
				if(r<0)continue;
				if(r==l)l-=eps,r+=eps;
				++ccnt;
				a[ccnt].x=calc(cnt,l);
				a[ccnt].y=calc(cnt,r)-1;
				a[ccnt].h=bomber[j][1];
				a[ccnt].isb=j;
			}
			for(int j=1;j<=n;++j)
			{
				if(plane[j][0]>mis[i])continue;
				//if(plane[j][1]/double(vk)*vn>mis[i]+eps)continue;
				double l=(mis[i]-plane[j][0]-1)/double(vn)-plane[j][1]/double(vk);
				l=max(l,0.);
				double r=(mis[i]-plane[j][0])/double(vn)-plane[j][1]/double(vk);
				if(r<0)continue;
				if(r==l)l-=eps,r+=eps;
				++ccnt;
				a[ccnt].x=calc(cnt,l);
				a[ccnt].y=calc(cnt,r)-1;
				a[ccnt].h=plane[j][1];
				a[ccnt].isb=0;
			}
			memset(use,0,sizeof(use));
			stable_sort(a+1,a+ccnt+1);
			for(int j=1;j<=ccnt;++j)
			{
				if(a[j].isb)
				{
					bool OK=false;
					for(int l=a[j].x;l<=a[j].y;++l)
						if(!use[l])
						{
							OK=1;
							break;
						}
					if(OK)
					{
						g[i].push_back(a[j].isb);
						//printf("%d %d\n",i,a[j].isb);
					}
				}
				for(int l=a[j].x;l<=a[j].y;++l)
					use[l]=1;
			}
		}
		memset(lk,0,sizeof(lk));
		//memset(vis,0,sizeof(vis));
		int ans=0;
		for(int i=1;i<=k;++i)
		{
			memset(vis,0,sizeof(vis));
			if(find(i))
				++ans;
		}
		printf("Mission #%d: %d bomber(s) exploded\n",cas,ans);
	}
	return 0;
}
/*
0.0000 0.0000
47.0000 48.0000

1 2
99.0000 100.0000
0.0000 1.0000
147.0000 148.0000

2 2
199.0000 200.0000
100.0000 101.0000
247.0000 248.0000

3 2
Mission #2: 1 bomber(s) exploded
*/
