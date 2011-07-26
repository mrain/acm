#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (1600000)

const int bound=1500000;

int pre[maxn],suf[maxn];
bool flag[maxn];

void ready() {
	flag[1]=true;
	
	for (int i=2;i<=bound;i++) if (!flag[i]) {
		for (int k=i+i;k<=bound;k+=i) flag[k]=true;
	}
	
	for (int i=2;i<=bound;i++) {
		if (!flag[i]) pre[i]=i;
		else pre[i]=pre[i-1];
	}
	
	for (int i=bound;i>=2;i--) {
		if (!flag[i]) suf[i]=i;
		else suf[i]=suf[i+1];
	}
}

int main() {
	ready();

	for (int n;scanf("%d",&n)==1&&n;) {
		if (!flag[n]) puts("0");
		else printf("%d\n",suf[n]-pre[n]);
	}

	return 0;
}
