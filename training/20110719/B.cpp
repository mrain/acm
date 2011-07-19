#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (10000)

int n,m,s;
int f[maxn];

bool cmp(int a,int b) {
	return a>b;
}	

int main(){
	scanf("%d%d%d",&n,&m,&s);
	
	m*=s;
	for (int i=1;i<=n;i++) scanf("%d",&f[i]);
	
	sort(f+1,f+1+n,cmp);
	
	for (int i=1;i<=n;i++) {
		m-=f[i];
		
		if (m<=0) {
			printf("%d\n",i); return 0; 
		}
	}

	return 0;
}
