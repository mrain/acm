#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int ans[1100];

int main(){
	for (int i=1;i<=1000;i++) ans[i]=ans[i-1]+((i*i+i)/2);

	int T,n; scanf("%d",&T);
	
	for (int t=1;t<=T;t++) {
		scanf("%d",&n);
		
		printf("%d: %d %d\n",t,n,ans[n]);
	}

	return 0;
}
