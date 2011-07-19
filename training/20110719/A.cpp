#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
	int n,ans=0;
	
	scanf("%d",&n);
	
	for (int i=1;i<=n;i++)
		ans+=n/i;
	
	for (int i=1;i<=n&&i*i<=n;i++)
		ans++;
		
	ans/=2;
	
	printf("%d\n",ans);

	return 0;
}
