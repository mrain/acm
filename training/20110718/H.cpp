#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define A first
#define B second
using namespace std;
int n,m,d[211][211];
char s[211][211];
queue< pair<int,int> > q;
int main()
{
	while(scanf("%d%d",&n,&m),n||m)
	{
		memset(s,' ',sizeof(s));
		memset(d,0,sizeof(d));
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
			{
				char ch=' ';
				while(ch!='S'&&ch!='W'&&ch!='B')ch=getchar();
				s[i][j]=ch;
			}
		int ur,dr;
		for(ur=m;ur;--ur)
			if(s[1][ur]=='S')
				break;
		for(dr=m;dr;--dr)
			if(s[n][dr]=='S')
				break;
		for(int i=1;i<=n;++i)
			for(int j=m;j>0;--j)
				if(s[i][j]=='S')
				{
					if(j!=m-1)
						s[i][j+1]='S';
					break;
				}
		while(!q.empty())q.pop();
		q.push(make_pair(1,ur));
		d[1][ur]=1,s[1][ur]=' ';
		if(s[1][ur+1]=='S')
		{
			q.push(make_pair(1,ur+1));
			d[1][ur+1]=1;
			s[1][ur+1]=' ';
		}
		int ans=0;
		while(!q.empty())
		{
			pair<int,int> p=q.front();
			q.pop();
			if(p.A==n&&(p.B==dr||p.B==dr+1))
			{
				ans=d[p.A][p.B];
				break;
			}
			int x=p.A,y=p.B;
			if(s[x+1][y]=='S')
			{
				d[x+1][y]=d[x][y]+1;
				s[x+1][y]=' ';
				q.push(make_pair(x+1,y));
			}
			if(s[x][y-1]=='S')
			{
				d[x][y-1]=d[x][y]+1;
				s[x][y-1]=' ';
				q.push(make_pair(x,y-1));
			}
			if(s[x][y+1]=='S')
			{
				d[x][y+1]=d[x][y]+1;
				s[x][y-1]=' ';
				q.push(make_pair(x,y+1));
			}
		}/*
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=m;++j)
				printf("%d ",d[i][j]);
			puts("");
		}	*/	
		printf("%d\n",ans);
	}
	return 0;
}
