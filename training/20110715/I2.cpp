#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (700)

int pre[maxn],dis[maxn],vh[maxn],now[maxn],his[maxn];
int g[maxn][maxn];
int nx[maxn],ny[maxn],nv[maxn],nr[maxn],ix[maxn],iy[maxn],iv[maxn];
int N,M,n,st,ed,flow;

const int inf=100000;

bool reach(int a,int b) {
	return nr[a]*nr[a]>=(nx[a]-ix[b])*(nx[a]-ix[b])+(ny[a]-iy[b])*(ny[a]-iy[b]);
}

void add(int a,int b,int c) {
	g[a][b]=c;
}

int DFS(int u,int t)
{
	if(u==ed)return t;
	int l=t,minh=ed+1;
	for(int v=1;v<=n;++v)
	{
		if(!g[u][v])continue;
		if(dis[u]==dis[v]+1)
		{
			int tmp=min(l,g[u][v]);
			tmp=DFS(v,tmp);
			g[u][v]-=tmp;
			g[v][u]+=tmp;
			l-=tmp;
			if(!l)
				return t-l;
			if(dis[st]>n)break;
		}
		minh=min(minh,dis[v]);
	}
	if(l==t)
	{
		vh[dis[u]]--;
		if(!vh[dis[u]])
			dis[st]=n+1;
		dis[u]=minh+1;
		++vh[dis[u]];
	}
	return t-l;
}

void SAP(){
	n=ed,flow=0;

	memset(vh,0,sizeof(vh));
	memset(pre,0,sizeof(pre));
	memset(dis,0,sizeof(dis));
	memset(his,0,sizeof(his));
	for (int i=1;i<=n;i++) now[i]=1;
	vh[0]=n;
	
	int aug=inf,i=1;
	
	while(dis[st]<=n)
		flow+=DFS(1,inf);
/*	
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=n;j++) printf("%d ",g[i][j]); puts("");
	}
	for (int i=1;i<=N;i++) printf("%d ",nv[i]); puts("");
	for (int i=1;i<=M;i++) printf("%d ",iv[i]); puts("");
	printf("%d\n",flow);
*/
}

void work(){
	scanf("%d%d",&N,&M);
	for (int i=1;i<=N;i++) scanf("%d%d%d%d",&nx[i],&ny[i],&nv[i],&nr[i]);
	for (int i=1;i<=M;i++) scanf("%d%d%d",&ix[i],&iy[i],&iv[i]);
	
	//Calc thyself
	for (int i=1;i<=M;i++) if (reach(1,i)) {
		nv[1]+=iv[i]; iv[i]=0;		
	}
	
	//Exclude rubbish
	for (int i=1;i<=M;i++) if (iv[i]) {
		bool flag=false;
	
		for (int k=1;k<=N;k++) 
			if (reach(k,i)) {
				flag=true; break;
			}
		
		if (!flag) iv[i]=0;
	}
	
	//Initial fail
	for (int i=2;i<=N;i++) if (nv[1]<nv[i]) {
		puts("Lonesome Willy"); return ;
	}
	
	//Add edge
	memset(g,0,sizeof(g));
	st=1,ed=1+N+M;
	for (int i=2;i<=N;i++) add(st,i,nv[1]-nv[i]);
	for (int i=2;i<=N;i++)
		for (int j=1;j<=M;j++)
			if (reach(i,j)) add(i,N+j,inf);
	for (int i=1;i<=M;i++) add(i+N,ed,iv[i]);
	
	//SAP
	SAP(); 
	
	int tot=0;
	for (int i=1;i<=M;i++) tot+=iv[i];
	if (tot>flow) puts("Lonesome Willy");
	else puts("Suiting Success");
}

int main(){
	int T; scanf("%d",&T);
	
	while (T--) work();

	return 0;
} 
