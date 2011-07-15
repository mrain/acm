#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>

using namespace std;

#define maxn (100)

char g[maxn][maxn];
int m,n;

char cmds[maxn],txt[10000];

void fill(int a,int b,char c) {
	if (a<=0||b<=0||a>m||b>n) return ;
	
	if (g[a][b]==c||c==' '||g[a][b]==' ') {
		g[a][b]=c; return ;
	}
	
	if (g[a][b]=='+'&&(c=='-'||c=='|')) return ;
	if (g[a][b]=='x'&&(c=='\\'||c=='/')) return ;
	
	if (g[a][b]=='|'&&c=='-'||g[a][b]=='-'&&c=='|') {
		g[a][b]='+'; return ;
	}
	
	if (g[a][b]=='\\'&&c=='/'||g[a][b]=='/'&&c=='\\') {
		g[a][b]='x'; return ;
	}
	
	g[a][b]='*';
}

void clear(){
	int a,b,c,d; scanf("%d%d%d%d",&b,&a,&d,&c);
	
	if (a>c) swap(a,c); if (b>d) swap(b,d);
	
	for (int i=a;i<=c;i++)
		for (int j=b;j<=d;j++)
			fill(i,j,' ');
}

void text(){
	int a,b; scanf("%d%d%s",&b,&a,txt);
	
	for (int i=0;txt[i];i++) 
		fill(a,b+i,txt[i]);
}

void line(){
	int a,b,c,d; scanf("%d%d%d%d",&b,&a,&d,&c);
	
	int p=c-a,q=d-b;
	
	char x;
	
	if (p==0) x='-';
	if (q==0) x='|';
	if (p*q>0) x='\\';
	if (p*q<0) x='/';
	
	int t=max(abs(p),abs(q));
	p/=t,q/=t;
	
	for (int i=0;i<=t;i++)
		fill(a+i*p,b+i*q,x);
}

void point(){
	int a,b; scanf("%d%d",&b,&a);
	
	fill(a,b,'o');
}

int main(){
	
	while (scanf("%d%d",&n,&m)==2&&(n||m)) {
		memset(g,' ',sizeof(g));
		for (int i=0;i<=m+1;i++) g[i][0]=g[i][n+1]='|';
		for (int i=0;i<=n+1;i++) g[0][i]=g[m+1][i]='-';
		
		g[0][0]=g[0][n+1]=g[m+1][0]=g[m+1][n+1]='+';
	
		while (scanf("%s",cmds)==1&&(cmds[0]!='P'||cmds[1]!='R')) {
			if (cmds[0]=='P') point();
			if (cmds[0]=='T') text();
			if (cmds[0]=='L') line();
			if (cmds[0]=='C') clear();
		}
		
		for (int i=0;i<=m+1;i++) {
			for (int j=0;j<=n+1;j++) 
				putchar(g[i][j]);
			puts("");		
		}
		
		puts("");
	}

	return 0;
}
