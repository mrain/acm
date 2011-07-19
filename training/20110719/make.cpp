#include<cstdio>
#include<ctime>
#include<cstdlib>
int main()
{
	freopen("E.in","w",stdout);
	srand(unsigned(time(0)));
	printf("2000\n");
	for(int i=1;i<=2000;++i)
		printf("%d\n",rand()%1000000+1);
	return 0;
}
