#include<cstdio>
#include<set>
#include<cstring>
using namespace std;
int n,s,a[100003],cnt[100003];
bool can[100003];
set<int> h;
int main()
{
	int _;
	for(scanf("%d",&_);_--;)
	{
		scanf("%d%d",&n,&s);
		memset(a,0,sizeof(a));
		for(int i=1;i<=s;++i)
			scanf("%d",a+i);
		h.clear();
		int last;
		for(int i=s;i>=0;--i)
		{
			if(i==0||h.count(a[i]))
			{
				last=i;
				break;
			}
			h.insert(a[i]);
		}
		memset(can,0,sizeof(can));
		memset(cnt,0,sizeof(cnt));
		int l=1;
		for(int r=1;r<=s;++r)
		{
			++cnt[a[r]];
			while(cnt[a[r]]>1)
				--cnt[a[l]],++l;
			if(r-l+1==n)
				can[l]=true;
		}
		h.clear();
		int ans=0;
		for(int i=1;i<=n;++i)
		{
			if(i!=1&&a[i-1]&&h.count(a[i-1]))
				break;
			if(i!=1)h.insert(a[i-1]);
			int j=i;
			while(can[j])
				j+=n;
			if(j>last)++ans;
		}
		printf("%d\n",ans);
	}
	return 0;
}
