#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};
char s[1003][1003];
int q[1000003][2],m[1003];
int main()
{
	for(;;)
	{
		int n=0;
		while(scanf("%s",s[n]))
		{
			m[n]=strlen(s[n]);
			if(s[n]>='0'&&s[n]<='9')
				break;
			++n;
		}
		int _;
		for(sscanf(s[n],"%d",&_);_--;)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			--x,--y;
			char ch=s[x][y];
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
					if(aa<0||aa>=n||bb<0||bb>=m[aa])continue;
					if(s[aa][bb]!=ch)continue;
					s[aa][bb]=' ';
					q[r][0]=aa;
					q[r][1]=bb;
					r++;
				}
			}
			int maxm=0;
			for(int i=1;i<=n;++i)
			{
				int mm=0;
				for(int j=0;j<m[i];++j)
					if(s[i][j]!=' ')
						s[i][mm++]=s[i][j];
				m[i]=mm;
				maxm=max(maxm,mm);
			}
			for(int j=1;j<=maxm;++j)
				for(int 
		}
	}
	return 0;
}
