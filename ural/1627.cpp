#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#define num(x,y) b[(x)][(y)]
using namespace std;
const int MOD=1000000000;
int n,m,cnt,b[101][101];
long long a[101][101];
char s[11][11];
void out()
{
	for(int i=1;i<=cnt;++i)
		for(int j=1;j<=cnt;++j)
		{
			cout<<a[i][j];
			if(j==cnt)puts("");
			else putchar(' ');
		}
	puts("");
}
int main()
{
	scanf("%d%d",&n,&m);
	cnt=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			char ch=getchar();
			while(ch!='.'&&ch!='*')ch=getchar();
			s[i][j]=ch;
			if(s[i][j]=='.')b[i][j]=++cnt;
		}
	if(!cnt)
	{
		puts("0");
		return 0;
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int k=1;k<=n;++k)
				for(int l=1;l<=m;++l)
					if(abs(i-k)+abs(j-l)==1&&s[i][j]==s[k][l]&&s[i][j]=='.')
					{
						--a[num(i,j)][num(k,l)];
						++a[num(i,j)][num(i,j)];
					}
	//out();
	--cnt;
	for(int i=1;i<=cnt;++i)
		for(int j=1;j<=cnt;++j)
			a[i][j]=(a[i][j]+MOD)%MOD;
	long long ans=1;
	for(int i=1;i<=cnt;++i)
	{
		for(int j=i+1;j<=cnt;++j)
			if(j!=i)
			{
				while(a[j][i])
				{
					long long tmp=a[i][i]/a[j][i];
					for(int k=i;k<=cnt;++k)
					{
						long long x=(a[i][k]-tmp*a[j][k])%MOD;
						a[i][k]=a[j][k];
						a[j][k]=x;
					}
					ans*=-1;
				}
			}
		//out();
		ans=ans*a[i][i]%MOD;
		while(ans<0)ans+=MOD;
		if(!ans)break;
	}
	while(ans<0)ans+=MOD;
	//out();
	cout<<ans<<endl;
	return 0;
}

