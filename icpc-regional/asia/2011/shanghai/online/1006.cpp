#include<cstdio>
#include<utility>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,a[7][7],num[7][7];
pair<int,int> pos[23];
long long f[65537][17];
bool inBoard(int x,int y){
	return x>0&&x<=n&&y>0&&y<=m;
}
int main(){
	while(scanf("%d%d",&n,&m)==2){
		int id=0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j){
				scanf("%d",a[i]+j);
				if(a[i][j]==0){
					num[i][j]=++id;
					pos[id]=make_pair(i,j);
				}
			}
		memset(f,0,sizeof(f));
		for(int i=1;i<=id;++i)
			f[1<<(i-1)][i]=1;
		for(int i=0;i<(1<<id);++i)
			for(int j=1;j<=id;++j)
				if(f[i][j]&&(i&(1<<(j-1)))){
					//cout<<i<<" "<<j<<" "<<f[i][j]<<endl;
					int x=pos[j].first;
					int y=pos[j].second;
					for(int dx=1-x;dx<=n-x;++dx)
					for(int dy=1-y;dy<=n-y;++dy){
						if(__gcd(abs(dx),abs(dy))!=1)continue;
						int xx=x+dx;
						int yy=y+dy;
							if(a[xx][yy]==0&&!(i&(1<<num[xx][yy]-1)))
								f[i|(1<<num[xx][yy]-1)][num[xx][yy]]+=f[i][j];
							else if(a[xx][yy]!=1){
								int xxx=xx+dx;
								int yyy=yy+dy;
								if(inBoard(xxx,yyy)&&a[xxx][yyy]==0&&!(i&(1<<num[xxx][yyy]-1)))
									f[i|(1<<num[xxx][yyy]-1)][num[xxx][yyy]]+=f[i][j];
							}
					}
				}
		long long ans=0;
		for(int i=1;i<=id;++i)
			ans+=f[(1<<id)-1][i];
		cout<<ans<<endl;
	}
	return 0;
}
