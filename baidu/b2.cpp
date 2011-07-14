#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
int a1[110],a2[110],b1[110],b2[110],a[110][110],s[110][110],f[110][110],g[110][110];
int main()
{
while (1)
{
int n,m;
scanf("%d%d",&n,&m);
if (!n && !m)
break;
n++,m++;
int Q;
scanf("%d",&Q);
memset(a,0,sizeof(a));
while (Q--)
{
int x,y;
scanf("%d%d",&x,&y);
x++,y++;
a[x][y]=1;
}
for (int i=1;i<=n;i++)
for (int j=1;j<=m;j++)
s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
memset(f,63,sizeof(f));
memset(g,63,sizeof(g));
memset(a1,63,sizeof(a1));
memset(a2,63,sizeof(a2));
memset(b1,63,sizeof(b1));
memset(b2,63,sizeof(b2));
for (int i=1;i<=n;i++)
for (int j=1;j<=m;j++)
{
if (i>28 && j>15)
{
int x=i-28,y=j-15;
f[i][j]=s[i-1][j-1]-s[i-1][y]-s[x][j-1]+s[x][y];
a1[i]=min(a1[i],f[i][j]);
a2[x]=min(a2[x],f[i][j]);
b1[j]=min(b1[j],f[i][j]);
b2[y]=min(b2[y],f[i][j]);
}
if (i>15 && j>28)
{
int x=i-15,y=j-28;
g[i][j]=s[i-1][j-1]-s[i-1][y]-s[x][j-1]+s[x][y];
a1[i]=min(a1[i],g[i][j]);
a2[x]=min(a2[x],g[i][j]);
b1[j]=min(b1[j],g[i][j]);
b2[y]=min(b2[y],g[i][j]);
}
}
for (int i=2;i<=n;i++)
a1[i]=min(a1[i],a1[i-1]);
for (int i=n-1;i;i--)
a2[i]=min(a2[i],a2[i+1]);
for (int i=2;i<=m;i++)
b1[i]=min(b1[i],b1[i-1]);
for (int i=m-1;i;i--)
b2[i]=min(b2[i],b2[i+1]);
int ans=1<<30;
for (int i=1;i<=n;i++)
ans=min(ans,a1[i]+a2[i]);
for (int i=1;i<=m;i++)
ans=min(ans,b1[i]+b2[i]);
printf("%d\n",ans);
}
return(0);
}
