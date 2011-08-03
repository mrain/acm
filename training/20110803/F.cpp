#include<cstdio>
#include<cstring>
int n,A,s[1003][1003];
bool use[1003];

inline int get(int x1, int y1, int x2, int y2) {
++ x2, ++ y2;
		if(y2>1000) y2=1000;
		if(x2>1000) x2=1000;
		return s[x2][y2]-s[x2][y1-1]-s[x1-1][y2]+s[x1-1][y1-1];
}

int main()
{
	int _;
	for(scanf("%d",&_);_--;)
	{
		memset(s,0,sizeof(s));
		memset(use,0,sizeof(use));
		scanf("%d%d",&n,&A); 
		for(int i=1;i<=n;++i)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			s[x][y]++;
			use[x]=1;
		}
		for(int i=1;i<=1002;++i)
			for(int j=1;j<=1002;++j)
				s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
		int ans=0;
		for(int i=1;i<=1000;++i)
			if(use[i])
				for(int j=i;j<=1000;++j) {
					if(use[j]) {
						if (j - i + 1 > A) break;
						int delta = A / (j - i + 1);
						int x2=j;
						int x1=i;
						for(int k=1;k<=1001;++k)
						{
							int y1=k;
							int y2=y1+delta-1;
							//printf("%d %d\n",i,j);
							if(y2>1000) y2=1000;
							int tmp=s[x2+1][y2+1]-s[x2+1][y1-1]-s[x1-1][y2+1]+s[x1-1][y1-1];
							if(tmp>ans)
								ans=tmp;
							if (y2 >= 1000) break;
						}
					}
				}
		printf("%d\n",ans);
	}
	return 0;
}
