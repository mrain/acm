#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include <cstdlib>
#include<iostream>
#define num(x,y) b[(x)][(y)]
using namespace std;
int n,m,cnt,b[101][101];
long double a[101][101],t[101];
char s[11][11];
void out()
{
	for(int i=1;i<=cnt;++i)
		for(int j=1;j<=cnt;++j)
		{
			cout<<a[i][j]<<endl;
			//printf("%.2f",a[i][j]);
			if(j==cnt)puts("");
			else putchar(' ');
		}
	puts("");
}
int main()
{
cout.setf(ios::fixed);
cout.precision(0);
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
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int k=1;k<=n;++k)
				for(int l=1;l<=m;++l)
					if(abs(i-k)+abs(j-l)==1&&s[i][j]==s[k][l]&&s[i][j]=='.')
					{
						a[num(i,j)][num(k,l)]-=1;
						a[num(k,l)][num(k,l)]+=1;
					}
	//out();
	--cnt;
	long double ans=1;
	for(int i=1;i<=cnt;++i)
	{
		int id;
		for(id=i;id<=cnt;++id)
			if(a[id][i])
				break;
		if(id>cnt)
		{
			puts("0");
			return 0;
		}
		for(int j=1;j<=cnt;++j)
			swap(a[id][j],a[i][j]);
		//out();
		long double tmp=a[i][i];
		ans*=a[i][i];
		//ans=fmod(ans,1000000000);
		for(int j=1;j<=cnt;++j)
			a[i][j]/=tmp;
		//out();
		//printf("%.8f\n",ans);
		for(int j=1;j<=cnt;++j)
			if(j!=i)
			{
				tmp=a[j][i];
				for(int k=1;k<=cnt;++k)
					a[j][k]-=tmp*a[i][k];
			}
		//out();
	}
	printf("%Lf\n", ans);
	//printf("%d\n",(int)(fabs(ans)+1e-8));
	cout << fmod(ans,1000000000) << endl;
	return 0;
}
