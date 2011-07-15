#include<cstdio>
#include<cstring>
char s[10003];
int cnt[26];
int main()
{
	int _;
	for(scanf("%d%*c",&_);_--;)
	{
		gets(s);
		int len=strlen(s);
		memset(cnt,0,sizeof(cnt));
		for(int i=0;i<len;++i)
			if(s[i]>='A'&&s[i]<='Z')
				++cnt[s[i]-'A'];
		int ma=0,maa=0;
		for(int i=0;i<26;++i)
			if(cnt[i]==ma)
				++maa;
			else if(cnt[i]>ma)
				ma=cnt[i],maa=1;
		if(maa>1)
		{
			puts("NOT POSSIBLE");
			continue;
		}
		int d;
		for(int i=0;i<26;++i)
			if(cnt[i]==ma)
			{
				d=i-('E'-'A');
				if(d<0)d+=26;
			}
		printf("%d ",d);
		for(int i=0;i<len;++i)
			if(s[i]>='A'&&s[i]<='Z')
			{
				int v=s[i]-'A';
				putchar('A'+((v-d)+52)%26);
			}
			else putchar(s[i]);
		puts("");
	}
	return 0;
}
