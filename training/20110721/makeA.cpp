#include<cstdio>
#include<cstdlib>
#include<ctime>
bool del[10003];
int main()
{
	freopen("A.in","w",stdout);
	puts("128 8000");
	srand(unsigned(time(0)));
	for(int i=1;i<=128;++i)
	{
		int tmp=rand()%4000+1;
		while(del[tmp]==1)tmp=rand()%4000+1;
		del[tmp]=1;
	}
	int cnt=0;
	for(int i=1;i<128;++i)
		for(int j=i+1;j<=128;++j) 
		{
			++cnt;
			if(!del[cnt])
				printf("%d %d\n",i,j);
		}
	return 0;
}
