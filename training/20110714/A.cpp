#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int oo=(~0U>>1);
int n,cnt[103],sum[103],avg,delta;
struct edge
{
	int y,v,nt;
	edge(){}
	edge(int _y,int _v,int _nt):y(_y),v(_v),nt(_nt){}
}e[303];
int ed[103],CntEdge;
long long f[103][103],g[103];
void DFS(int fa,int u)
{
	cnt[u]=1;
	for(int i=ed[u];i;i=e[i].nt)
	{
		if(fa^1==i)continue;
		int j=e[i].y;
		DFS(i,j);
		cnt[u]+=cnt[j];
		sum[u]+=sum[j];
	}
	//printf("%d %d %d\n",u,cnt[u],sum[u]);
}
void DP(int fa,int u)
{
	for(int i=ed[u];i;i=e[i].nt)
	{
		if(fa^1==i)continue;
		int j=e[i].y;
		DP(i,j);
	}
	int cntnode=0;
	f[u][0]=0;
	for(int i=ed[u];i;i=e[i].nt)
	{
		if(fa^1==i)continue;
		int j=e[i].y;
		for(int k=0;k<=cntnode;++k){
			g[k]=f[u][k],f[u][k]+=f[j][0];
			//if(u==1)printf("%d:%d\n",k,g[k]);
		}
		for(int k=cntnode;k>=0;--k)
			for(int l=1;l<=cnt[j];++l)
				f[u][k+l]=min(f[u][k+l],g[k]+f[j][l]);
		cntnode+=cnt[j];
	}
	for(int i=cnt[u]-1;i>=0;--i)
		if(f[u][i+1]>f[u][i])
			f[u][i+1]=f[u][i];
	for(int i=0;i<=cnt[u];++i)
	{
		int yiban=cnt[u]-i;
		int teshu=i;
		int dis=yiban*avg+teshu*(avg+1);
		int now=sum[u];
		f[u][i]+=abs(dis-now)*e[fa].v;
		//printf("%d %d %lld\n",u,i,f[u][i]);
	}
}
int main()
{
	while(scanf("%d",&n)==1)
	{
		for(int i=1;i<=n;++i)scanf("%d",sum+i);
		memset(ed,0,sizeof(ed));
		CntEdge=1;
		for(int i=1;i<n;++i)
		{
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			++x,++y;
			e[++CntEdge]=edge(y,z,ed[x]);
			ed[x]=CntEdge;
			e[++CntEdge]=edge(x,z,ed[y]);
			ed[y]=CntEdge;
		}
		DFS(0,1);
		avg=sum[1]/cnt[1];
		delta=sum[1]%cnt[1];
		memset(f,44,sizeof(f));
		DP(0,1);
		cout<<f[1][delta]<<endl;
	}
	return 0;
}
