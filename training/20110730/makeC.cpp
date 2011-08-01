#include<cstdio>
#include<ctime>
#include<cstdlib>
int main()
{
	freopen("CC.in","w",stdout);
	srand(unsigned(time(0)));
	for(int cas=1;cas<=10;++cas)
	{
		puts("50000");
		for(int i=1;i<=50000;++i)
//			printf("%d\n",rand()%800+1);
			printf("%d\n", 500000 - i);
	}
	puts("0");
	return 0;
}
