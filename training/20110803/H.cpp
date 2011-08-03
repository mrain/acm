#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int f[503][503][2],n,m,r,c,room[503][2];
inline void update(int &x,int y)
{
	if(y<x)x=y;
}
int main()
{
	int _;
	for(scanf("%d",&_);_--;)
	{
		scanf("%d%d%d%d",&n,&m,&r,&c);
		for(int i=1;i<=r;++i)
			scanf("%d%d",room[i],room[i]+1);
		if(c>1)c=1;
		memset(f,44,sizeof(f));
		f[n][m][c]=0;
		for(int i=1;i<=r;++i)
		{
			for(int j=0;j<=n;++j)
				for(int k=0;k<=m;++k)
					for(int l=0;l<=c;++l)
						if(f[j][k][l]<=100000000)
						{
							int v=f[j][k][l]+room[i][1];
							update(f[max(j-room[i][0],0)][k][c],v);
							update(f[j][max(k-room[i][0],0)][c],v);
							if(l&&room[i][0]>1&&j&&k)
								update(f[j-1][k-1][0],v);
						}
		}
		int ans=min(f[0][0][0],f[0][0][1]);
		if(ans<=100000000)
			printf("%d\n",ans);
		else puts("Impossible");
	}
	return 0;
}
