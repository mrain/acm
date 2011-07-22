#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
//   Last Change:  2011-07-22 17:42:54

#define maxn 205

int ne[maxn],ce[maxn],list[maxn][maxn],n,m,ans;
bool g[maxn][maxn];


/*基本思想,分三个集合,分别为R、P、X，代表当前已选，当前待选，当前不能选
 * 程序伪代码:
	BronKerbosch2(R,P,X):
       if P and X are both empty:
           report R as a maximal clique
       choose a pivot vertex u in P ? X
       for each vertex v in P \ N(u):
           BronKerbosch2(R 并 {v}, P 交 N(v), X 交 N(v))
           P := P \ {v}
           X := X 并 {v}
 * 
 */
inline void dfs(int size)//list序列1-ne[size]表示X集合，ne[size}+1-ce[size]表示P集合 
{
	if (ans>1000) return;
	int i,j,k,t,cnt,best=0;
	bool bb;
	if (ne[size]==ce[size]){
		if (ce[size]==0) ++ans;
		return;
	}
	for (t=0,i=1;i<=ne[size];++i)//选取主元(选取一个与PUX关联节点最多的)//选取主元后将不考虑主元所有邻居 
	{
		for (cnt=0,j=ne[size]+1;j<=ce[size];++j)
		if (!g[list[size][i]][list[size][j]]) ++cnt;
		if (t==0 || cnt<best) t=i,best=cnt;
	}
	
	if (t && best<=0) return;//终止态：X集合存在一个元素与P集合每一个点相连 
	
	for (k=ne[size]+1;k<=ce[size];++k)
	{
		if (t>0)
		{
			for (i=k;i<=ce[size];++i)
			if (!g[list[size][t]][list[size][i]]) break;
			swap(list[size][k],list[size][i]);//选取当前一个非主元邻居当作这次拓展点 
		}
		i=list[size][k];
		ne[size+1]=ce[size+1]=0;
		for (j=1;j<k;++j)
		if (g[i][list[size][j]])
			list[size+1][++ne[size+1]]=list[size][j];// X 交 N[i] 
		for (ce[size+1]=ne[size+1],j=k+1;j<=ce[size];++j)
		if (g[i][list[size][j]])
			list[size+1][++ce[size+1]]=list[size][j];//P 交 N[i] 
		
		dfs(size+1);
		++ne[size];//X 并 v 
		--best;
		
		for (j=k+1,cnt=0;j<=ce[size];++j)
		if (!g[i][list[size][j]]) ++cnt;
		if (t==0 || cnt<best) t=k,best=cnt;//重新选取主元 
		if (t && best<=0) break;
	}
}

inline void work()
{
	ne[0]=0;
	ce[0]=0;
	for (int i=1;i<=n;++i)
		list[0][++ce[0]]=i;
	ans=0;
	dfs(0);
}

int main()
{
	for (;scanf("%d%d",&n,&m)==2 && (n|m);)
	{
		memset(g,false,sizeof(g));
		for (int i=0;i<m;++i)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			g[a][b]=g[b][a]=true;
		}
		
		work();
		
		if (ans>1000) puts("Too many maximal sets of friends.");
		else printf("%d\n",ans);
	}
	return 0;
}
