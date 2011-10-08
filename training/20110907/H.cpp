#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int c,a[81][5];
bool ans[9][503];
int main(){
	int _,cas=0;
	for(scanf("%d",&_);_--;){
		scanf("%d",&c);
		for(int i=1;i<=c;++i)
			for(int j=0;j<5;++j)
				scanf("%x",a[i]+j);
		memset(ans,0,sizeof(ans));
		int id=1;
		for(int i=1;i<=c;++i){
			for(int j=0;j<5;++j){
				for(int k=1;k<=7;++k){
					ans[k][id]=(a[i][j]&1);
					a[i][j]>>=1;
				}
				if(i!=c||j!=4)++id;
			}
			if(i!=c)++id;
		}
		//printf("%d\n",id);
		printf("Case %d:\n",++cas);
		puts("");
		for(int i=1;i<=7;++i){
			for(int j=1;j<=id;++j)
				if(ans[i][j])
					putchar('#');
				else putchar(' ');
			puts("");
		}
		puts("");
	}
	return 0;
}
