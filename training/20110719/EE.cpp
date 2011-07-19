#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,a[2003],f[2003][2003],g[2003][2003];
int DP(int l,int r)
{
	if(l>r)return 0;
	if(l==r)
	{
		g[l][r]=l;
		return a[l];
	}
	int &ret=f[l][r],s1;
	if(ret!=-1)return ret;
	ret=(~0U>>1);
	for(int i=l;i<=r;++i)
	{
		int tmp=max(DP(l,i-1),DP(i+1,r))+a[i];
		if(tmp<ret)
			ret=tmp,s1=i;
	}
	g[l][r]=s1;
	return ret;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",a+i);
	memset(f,-1,sizeof(f));
	printf("%d\n",DP(1,n));/*
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
			if(g[i][j]<g[i][j-1])
				printf("%d %d %d\n",i,j,g[i][j-1]-g[i][j]);*/
	return 0;
}
