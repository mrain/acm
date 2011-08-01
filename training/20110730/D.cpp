//f[i][j] |= (!f[i - k * j][j] | f[i][j - k * i])
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define maxn (500000)
#define PB push_back

vector<bool> g[maxn];
int a[maxn],b[maxn];
int flag[maxn];
int m,n;
bool is1[maxn];

const int bound=50000;

int main(){
	a[1]=1,b[1]=2;
	for (int i=2;a[i-1]<=bound;i++) {
	
		a[i]=a[i-1]+b[i-1];
	
		if (b[i]==0) b[i]=3;
		b[a[i]]=2;
		
		//printf("%d\n",a[i]);
	}
	memset(is1, 0, sizeof(is1));
	for (int i = 1; a[i] <= bound; ++ i) is1[a[i]] = true;
	/*
	for (int i=1;a[i]<=bound;i++) {
		for (int j=a[i-1]+1;j<=a[i];j++) flag[j]=i;
	}
	
	*/
	int pos = 1;
	for (int i = 1; pos <= bound; ++ i) {
		if (is1[i]) flag[pos ++] = i;
		else flag[pos ++] = i, flag[pos ++] = i;
	}

	int cases=0;
	
	while (scanf("%d%d",&m,&n)==2) {
		printf("Case #%d:\n",++cases);
		
		for (int i=1;i<=m;i++) {
			for (int j=1;j<=n;j++) {
				if (i<=j) {
					if (flag[j]<=i) putchar('P');
					else putchar('H'); 
				} 
				else {
					if (flag[i]<=j) putchar('P');
					else putchar('H');
				}
			}
			
			puts("");
		}
/*		
		for (int i=1;i<=71;i++) printf("%d, %d\n",i,b[i]);
	
		for (int i=0;i<=m;i++) g[i].clear();
		for (int i=0;i<=m;i++) g[i].PB(false);
		for (int i=1;i<=n;i++) g[0].PB(false);
		
		for (int i=1;i<=m;i++)
			for (int j=1;j<=n;j++) {
				bool flag=true;
				
				if (i<=j) {
					for (int x=i,y=j-i;x>=0&&y>=0&&flag;y-=i) {
						if (g[x][y]) flag=false;
					}
				}
				if (i>=j) {
					for (int x=i-j,y=j;x>=0&&y>=0&&flag;x-=j) {
						if (g[x][y]) flag=false;
					}
				}
				
				g[i].PB(flag);
			}
			
		static int a[500000];
		for (int i=1;i<=m;i++) {
			for (int j=1;j<=n;j++) {
				if (g[i][j]) {
					//printf("%d,",j); break;
					a[i] = j; break;
				}
			
				//if (g[i][j]) putchar('P');
				//else putchar('H');
			}
			
			//putchar('\n');
		}
		vector <int> p;
		for (int i = 1; i <= m; ++ i)
			if (a[i] != a[i - 1] && a[i] != a[i + 1])
				//printf("%d\n", a[i]);
				p.push_back(a[i]);
		for (int i = 1; i < (int)p.size(); ++ i)
			printf("%d, %d\n", i, p[i] - p[i - 1]);
*/
	}
	

	return 0;
}
