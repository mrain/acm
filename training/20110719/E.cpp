#include<cstdio>
#include<algorithm>
using namespace std;
const int oo=(~0U>>1);
int n,a[2003],f[2003][2003],g[2003][2003];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	for(int i=1;i<=n;++i)
		f[i][i]=a[i],g[i][i]=i;
	for(int i=2;i<=n;++i)
		for(int j=1;j+i-1<=n;++j)
		{
			int st=j;
			int en=j+i-1;
			int &v=f[st][en],&v1=g[st][en];
			v=oo;
			for(int k=max(st,g[st][en-1]-50);k<=en;++k)
			{
				int tmp=max(f[st][k-1],f[k+1][en])+a[k];
				if(tmp<v)
					v=tmp,v1=k;
			}
		}
	printf("%d\n",f[1][n]);
	return 0;
}
