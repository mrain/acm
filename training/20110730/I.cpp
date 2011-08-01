#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define pb push_back
using namespace std;
int L,n1,n2;
vector<int> x;
struct interval
{
	int l,r;
}a[100003],b[100003];
int a1[400003],a2[400003];
int main()
{
	int cas=0;
	while(scanf("%d%d%d",&L,&n1,&n2)==3)
	{
		++cas;
		x.clear();
		x.pb(L+1);
		for(int i=1;i<=n1;++i)
		{
			scanf("%d%d",&a[i].l,&a[i].r);
			x.pb(a[i].l);
			x.pb(a[i].r+1);
		}
		for(int i=1;i<=n2;++i)
		{
			scanf("%d%d",&b[i].l,&b[i].r);
			x.pb(b[i].l);
			x.pb(b[i].r+1);
		}
		stable_sort(x.begin(),x.end());
		x.erase(unique(x.begin(),x.end()),x.end());
		for(int i=1;i<=n1;++i)
		{
			a[i].l=lower_bound(x.begin(),x.end(),a[i].l)-x.begin();
			a[i].r=lower_bound(x.begin(),x.end(),a[i].r+1)-x.begin();
		}
		for(int i=1;i<=n2;++i)
		{
			b[i].l=lower_bound(x.begin(),x.end(),b[i].l)-x.begin();
			b[i].r=lower_bound(x.begin(),x.end(),b[i].r+1)-x.begin();
		}
		for(int i=1;i<=n1;++i)
			for(int j=a[i].l;j<a[i].r;++j)
				a1[j]=cas;
		for(int i=1;i<=n2;++i)
			for(int j=b[i].l;j<b[i].r;++j)
				a2[j]=cas;
		int ans=0;
		for(int i=0;i<x.size();++i)
		{
			/*if(a1[i]==cas&&a2[i]==cas)a1[i]=a2[i]=0;
			if(a1[i]==cas||a2[i]==cas)
			{
				int beg=i;
				while(i!=x.size()-1&&(a1[i+1]==cas||a2[i+1]==cas)&&(a1[i+1]!=cas||a2[i+1]!=cas))
					++i;
				ans=max(ans,x[i+1]-x[beg]);
				printf("%d %d\n",x[beg],x[i+1]);
			}*/
			int beg = i;
			while (i != x.size() && (a1[i]==cas||a2[i]==cas)&&(a1[i]!=cas||a2[i]!=cas))
				++ i;
			ans = max(ans, x[i] - x[beg]);
			//printf("%d %d\n", x[beg], x[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
