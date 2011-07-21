#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>

using namespace std;

#define maxn (500000)

char s[maxn];
int g[maxn];
int now;

int calc(bool flag) {
	int x=g[++now];
	
	if (x==0) return 1;
	if (x==-1) return calc(!flag);

	if (flag) return calc(flag)+calc(flag);
	return max(calc(flag),calc(flag));
}

void work(){
	now=0;
	for (int i=0,n=0;s[i];i++) if (isupper(s[i])) {
		int x;
		if (s[i]=='U') x=1;
		if (s[i]=='V') x=0;
		if (s[i]=='C') x=-1;
		g[++n]=x;
	}
	
	printf("%d\n",calc(true));
}

int main(){
	
	while (gets(s)) work();

	return 0;
}
