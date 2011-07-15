#include<cstdio>
int main()
{
	int ans=0;
	for(int i=56789;i<=80001;++i)
		if(i%2==0||i%3==0||i%5==0||i%7==0||i%97==0)
			if(i%32767)
				++ans;
	printf("%d\n",ans);
	scanf("%d",&ans);
}
