#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (100)

int ans[maxn];
int n;

int main(){
	int T; scanf("%d",&T);
	
	for (int tt=1;tt<=T;tt++) {
		scanf("%d",&n);
		
		for (int i=0;i<=9;i++) ans[i]=0;
		
		for (int k=1;k<=n;k++) {
			int x=k;
			while (x) {
				ans[x%10]++;
				x/=10;
			}
		}
		
		for (int i=0;i<9;i++) printf("%d ",ans[i]);
		printf("%d\n",ans[9]);
	}

	return 0;
}
