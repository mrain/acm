#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
	int ca=0;
	scanf("%d",&ca);
	for(int cas=1;cas<=ca;++cas){
		int n;
		scanf("%d",&n);
		long long s1=0,s2=0;
		int v=(~0U>>1);
		for(int i=1;i<=n;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			s1+=x,s2+=y,v=min(v,y);
		}
		if(s1>=s2+v)printf("Case %d: Alice\n",cas);
		else printf("Case %d: Bob\n",cas);
	}
	return 0;
}
