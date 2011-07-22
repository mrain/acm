#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (10)

int g[maxn][maxn],f[maxn][maxn];
bool dis[maxn][maxn];
const int dx[4]={0,-1,0,1},dy[4]={-1,0,1,0};
const int n=8;

char buf[100];

bool dfs() {
/*
	puts("=============================");
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) putchar(g[i][j]+'0'); puts("");
	}
*/
	bool flag=false,rest=false;
	memset(dis,0,sizeof(dis));
	
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++) if (g[i][j]) {
			rest=true;
			int k=j;
			
			for (;k<n-1&&g[i][k]==g[i][k+1];k++) ;
			
			if (k-j+1>=3) {
				flag=true;
				for (int a=j;a<=k;a++) dis[i][a]=true;
			}
			
			j=k;
		}
		
	for (int j=0;j<n;j++)
		for (int i=0;i<n;i++) if (g[i][j]) {
			rest=true;
			int k=i;
			
			for (;k<n-1&&g[k][j]==g[k+1][j];k++) ;
			
			if (k-i+1>=3) {
				flag=true;
				for (int a=i;a<=k;a++) dis[a][j]=true;
			}
			
			i=k;
		}
	
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++) if (dis[i][j])
			g[i][j]=0;

	if (!rest) return true;
/*
	puts("+++++++++++++++++++++++++++++");
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) putchar(g[i][j]+'0'); puts("");
	}
*/
	for (int i=n-1;i>=0;i--)
		for (int j=0;j<n;j++) if (g[i][j]) {
			for (int k=i;k<n;k++) {
				if (k==n-1||g[k+1][j]) {
					g[k][j]=g[i][j]; if (k!=i) g[i][j]=0; break;
				}
			}
		}
	
	if (flag) return dfs();
	else return false;
}

bool ok(int i,int j,int k) {
	int x=i+dx[k],y=j+dy[k];
	
	if (x<0||x>=n||y<0||y>=n) return false;
	if (!f[i][j]&&!f[x][y]) return false;
 
	memcpy(g,f,sizeof(g));
			
	swap(g[i][j],g[x][y]);
	
	//printf("%d %d %d %d\n",i,j,x,y);
	
	return dfs();
}

bool work() {
	for (int i=0;i<n;i++) {
		scanf("%s",buf);
		
		if (buf[0]=='0') return false;
		
		for (int j=0;j<n;j++) 
			if (buf[j]!='.') f[i][j]=buf[j]-'0';
			else f[i][j]=0;
	}
	
	//ok(7,3,1);

	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++) 
			for (int k=0;k<2;k++) 
				if (ok(i,j,k)) {
					puts("Yes"); return true;
				}

	puts("No");
	return true;
}

int main(){
	while (work());

	return 0;
}

