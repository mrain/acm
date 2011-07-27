#include<cstdio>
#include<cstdlib>
#include<ctime>
int main()
{
	freopen("I.in","w",stdout);
	puts("10");
	srand(unsigned(time(0)));
	for(int cas=0;cas<9;++cas)
	{
		puts("100000 200000");
		for(int i=1;i<=100000;++i)
			printf("%d %d %d\n",i,rand()%i+1,rand());
		for(int i=1;i<=100000;++i)
			printf("%d %d %d\n",rand()%100000+1,rand()%100000+1,rand());
	}
	puts("100000 99999");
	for(int i=1;i<100000;++i)
		printf("%d %d %d\n",i,i+1,i);
	return 0;
}
