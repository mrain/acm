#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int MX=100003;
int n,d[MX];
vector<int> e[MX];
void DFS(int u,int fa)
{
	for(int i=0;i<e[u].size();++i)
	{
		int v=e[u][i];
		if(v==fa)continue;
		d[v]=d[u]+1;
		DFS(v,u);
	}
}
int main()
{
	int _;
	for(scanf("%d",&_);_--;)
	{
	    scanf("%d",&n);
	    for(int i=1;i<=n;++i)e[i].clear();
	    for(int i=1;i<n;++i)
	    {
	    	int x,y;
	    	scanf("%d%d",&x,&y);
	    	++x,++y;
	    	e[x].push_back(y);
	    	e[y].push_back(x);
	    }
	    memset(d,44,sizeof(d));
	    d[1]=0;
	    DFS(1,0);
	    int s1=2;
	    for(int i=3;i<=n;++i)
	    	if(d[i]>d[s1])
	    		s1=i;
	    memset(d,44,sizeof(d));
	    d[s1]=0;
	    DFS(s1,0);
	    int ans=0;
	    for(int i=1;i<=n;++i)
	    	if(d[i]>ans)
	    		ans=d[i];
	    printf("%d\n",(ans+1)/2);
	}
	return 0;
}
