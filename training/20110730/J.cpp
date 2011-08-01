#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;
int n,v;
multiset<int> h;
int main()
{
	while (1) {
		if (scanf("%d%d",&n,&v) != 2) break;
		h.clear();
		for(int i=1;i<=n;++i)
		{
			int x;
			scanf("%d",&x);
			h.insert(x);
		}
		for(;;)
		{
			multiset<int>:: iterator it=upper_bound(h.begin(),h.end(),v);
			if(it==h.end())break;
			v+=2;
			h.erase(it);
		}
		v+=h.size();
		printf("%d\n",v);
	}
	return 0;
}

