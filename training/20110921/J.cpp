#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,a[303][303],cnt[2][303][303];
int calc(int v,int x1,int y1,int x2,int y2){
	int ret=cnt[v][x2][y2];
	ret-=cnt[v][x2][y1-1];
	ret-=cnt[v][x1-1][y2];
	ret+=cnt[v][x1-1][y1-1];
	return ret;
}
int main(){
	int _;
	for(scanf("%d",&_);_--;){
		scanf("%d%d",&n,&m);
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j){
				scanf("%d",a[i]+j);
				cnt[0][i][j]=(a[i][j]==0)+cnt[0][i-1][j]+cnt[0][i][j-1]-cnt[0][i-1][j-1];
				cnt[1][i][j]=(a[i][j]==1)+cnt[1][i-1][j]+cnt[1][i][j-1]-cnt[1][i-1][j-1];
			}
		int ans=0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				for(int k=2;i+k-1<=n&&j+k-1<=m;++k)
					if(calc(0,i,j,i,j+k-1)==0)
						if(calc(0,i,j+k-1,i+k-1,j+k-1)==0)
							if(calc(0,i,j,i+k-1,j)==0)
								if(calc(0,i+k-1,j,i+k-1,j+k-1)==0)
									if(k==2||abs(calc(0,i+1,j+1,i+k-2,j+k-2)-calc(1,i+1,j+1,i+k-2,j+k-2))<=1)
										++ans;
		printf("%d\n",ans);
	}
	return 0;
}
