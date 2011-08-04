#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

double a[100][100];
double f[100];
int cnt;

void out()
{
	for(int i=1;i<=cnt;++i)
		for(int j=1;j<=cnt;++j)
		{
			cout<<a[i][j];
			//printf("%.2f",a[i][j]);
			if(j==cnt)puts("");
			else putchar(' ');
		}
	puts("");
}

int main() {
	cnt = 6;
	for (int i = 1; i <= cnt; ++ i)
		for (int j = 1; j <= cnt; ++ j) {
			int x = i + j;
			if (x == 2) a[i][j] = 1;
			if (x == 4) a[i][j] = 1;
			if (x == 6) a[i][j] = 2;
			if (x == 8) a[i][j] = 5;
			if (x == 10) a[i][j] = 14;
			if (x == 12) a[i][j] = 42;
		}
	out();
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
		for(int j=1;j<=cnt;++j)
			a[i][j]/=tmp;
		for(int j=1;j<=cnt;++j)
			if(j!=i)
			{
				tmp=a[j][i];
				for(int k=1;k<=cnt;++k)
					a[j][k]-=tmp*a[i][k];
			}
	}
	cout << ans << endl;
	return 0;
}

