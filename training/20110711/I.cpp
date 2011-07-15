#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

#define maxn (100)

typedef long long LL;

LL f[maxn][maxn];
int g[maxn];
int n;

int typ;

char buf[100000];

void init(){
	gets(buf); n=0;
	
	stringstream ss(buf);
	
	int x;
	while (ss >> x) g[++n]=x; 
	
	if (g[1]<g[2]) typ=1; else typ=2;
/*	
	for (int i=1;i<=n;i++) printf("%d ",g[i]); puts("");
*/
}

LL calc1(){
	memset(f,0,sizeof(f));
	LL ret=0ll;
	
	for (int i=1;i<g[1];i++) f[1][i]=1ll;
	
	for (int i=2;i<=18;i++) {
		if (i%2==0) {
			if ((typ==1||i==2)&&i-1<=n) for (int j=g[i-1]+1;j<g[i];j++) f[i][j]++;
			
			for (int j=1;j<=9;j++) 
				for (int k=j+1;k<=9;k++)
					f[i][k]+=f[i-1][j];
		}
		else {
			if ((typ==1||i==2)&&i-1<=n) for (int j=1;j<g[i]&&j<g[i-1];j++) f[i][j]++;
			
			for (int j=1;j<=9;j++)
				for (int k=1;k<j;k++)
					f[i][k]+=f[i-1][j];
		}
		
		if (i>=3) {
			if (i<n&&typ==1) ret++;
			
			for (int j=1;j<=9;j++) ret+=f[i][j];
		}
	}
/*	
	cout << "Calc1  :  " << ret << endl ;
*/
	return ret;
}

LL calc2(){
	memset(f,0,sizeof(f));
	LL ret=0ll;
	
	for (int i=1;i<g[1];i++) f[1][i]=1ll;
	
	for (int i=2;i<=18;i++) {
		if (i%2==1) {
			if ((typ==2||i==2)&&i-1<=n) for (int j=g[i-1]+1;j<g[i];j++) f[i][j]++;
			
			for (int j=1;j<=9;j++) 
				for (int k=j+1;k<=9;k++)
					f[i][k]+=f[i-1][j];
		}
		else {
			if ((typ==2||i==2)&&i-1<=n) for (int j=1;j<g[i]&&j<g[i-1];j++) f[i][j]++;
			
			for (int j=1;j<=9;j++)
				for (int k=1;k<j;k++)
					f[i][k]+=f[i-1][j];
		}
		
		if (i>=3) {
			if (i<n&&typ==2) ret++;
			
			for (int j=1;j<=9;j++) ret+=f[i][j];
		}
	}
/*	
	cout << "Calc2  :  " << ret << endl ;
*/	
	return ret;
}

void work(){
	LL ans=calc1()+calc2();
	
	cout << ans+1ll << endl ;
}

int main() {
	int T; scanf("%d",&T);
	gets(buf);
	
	for (int tt=1;tt<=T;tt++) {
		init(); work();
	}

	return 0;
}
