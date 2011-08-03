#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};
char s[1003][1003];
int q[1000003][2];
int main()
{
	int cas=0;
	for(;;)
	{
		int n=0,m;
		while(scanf("%s",s[n])!=EOF)
		{
			if(s[n][0]>='0'&&s[n][0]<='9')
				break;
			++n;
		}
		if(!n)break;
		m=strlen(s[0]);
		int _,emp=0;
		for(sscanf(s[n],"%d",&_);_--;)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			x=(x-1)+emp,--y;
			char ch=s[x][y];
			if(ch==' ')continue;
			s[x][y]=' ';
			int l=0,r=1;
			q[l][0]=x,q[l][1]=y;
			while(l!=r)
			{
				int a=q[l][0];
				int b=q[l][1];
				++l;
				for(int i=0;i<4;++i)
				{
					int aa=a+dx[i];
					int bb=b+dy[i];
					if(aa<0||aa>=n||bb<0||bb>=m)continue;
					if(s[aa][bb]!=ch)continue;
					s[aa][bb]=' ';
					q[r][0]=aa;
					q[r][1]=bb;
					r++;
				}
			}
			for(int i=0;i<n;++i)
			{
				int mm=0;
				for(int j=0;j<m;++j)
					if(s[i][j]!=' ')
						s[i][mm++]=s[i][j];
				for(int j=mm;j<m;++j)
					s[i][j]=' ';
			}
			for(int j=0;j<m;++j)
			{
				int nn=n-1;
				for(int i=n-1;i>=0;--i)
					if(s[i][j]!=' ')
						s[nn--][j]=s[i][j];
				for(int i=nn;i>=0;--i)
					s[i][j]=' ';
			}
			while (emp<n && s[emp][0] == ' ') ++ emp;
		}
		printf("Test case #%d:\n",++cas);
		if (emp==n)puts("");
		for(int i=0;i<n;++i)
		{
			bool flag=false;	
			for(int j=0;j<m;++j)
				if(s[i][j]!=' ')
				{
					flag=true;
					putchar(s[i][j]);
				}
			if(flag)puts("");
		}
	}
	return 0;
}
