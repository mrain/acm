#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
struct door
{
	int dep,id;
	door(){}
	door(int dep,int id):dep(dep),id(id){}
};
int n,k,m,d[11][51];
vector<door> g[11][51];
queue<door> q;
int main()
{
	scanf("%d%d",&n,&k);
	scanf("%d ",&m);
	for(int i=1;i<=m;++i)
	{
		int x1,y1;
		int x2,y2;
		scanf(" %d ",&x1);
		scanf(" . ");
		scanf(" %d ",&y1);
		scanf(" - ");
		scanf(" %d ",&x2);
		scanf(" . ");
		scanf(" %d ",&y2);
		//printf("%d %d %d %d\n",x1,y1,x2,y2);
		
		if (x1>x2) {
			swap(x1,x2),swap(y1,y2);
		}
		
		if (x1==x2)
	}
	memset(d,-1,sizeof(d));
	int S,T;
	scanf("%d%d",&S,&T);
	d[0][S]=0;
	q.push(door(0,S));
	while(!q.empty())
	{
		door x=q.front();q.pop();
		for(int i=0;i<g[x.dep][x.id].size();++i)
		{
			door y=g[x.dep][x.id][i];
			if(d[y.dep][y.id]==-1)
			{
				d[y.dep][y.id]=d[x.dep][x.id]+1;
				q.push(y);
			}
		}
	}
	if(d[0][T]==-1)puts("no solution");
	else printf("%d\n",d[0][T]);
	return 0;
}
