#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <cctype>
#include <vector>

using namespace std;

#define maxn (200000)
#define A first
#define B second
#define MP make_pair

typedef long long LL;
typedef pair<LL,LL> PII;
typedef pair<PII,LL> PIII;

char s[maxn];
vector<PIII> hash[maxn];
int g[maxn],mark[maxn];
int n,cnt,cases;
LL Pow[100];
LL a,b,c;

char buf[100];

const LL mod=198357;

void add(int x) {
	g[cnt++]=x;
	
	if (x<9) {
		a+=Pow[x]; return ;
	}
	
	if (x<18) {
		b+=Pow[x-9]; return ;
	}
	
	c+=Pow[x-18];
}

void del(int x) {
	if (x<9) {
		a-=Pow[x]; return ;
	}
	
	if (x<18) {
		b-=Pow[x-9]; return ;
	}
	
	c-=Pow[x-18];
}

bool insert(){
	PIII v=MP(MP(a,b),c);
	int x=(int)(((a<<7ll)|(b<<4ll)|(c))%mod);
/*
	cout << a << ' ' << b << ' ' << c << ' ' << x << endl ; 
*/
	if (mark[x]!=cases) hash[x].clear(),mark[x]=cases;

	for (int i=0;i<hash[x].size();i++) if (hash[x][i]==v) return false;
	
	hash[x].push_back(v);

	return true;
}

bool calc(){
	if (!insert()) return true;
	
	del(g[cnt-n]);
	
	return false;
}

void work(){
	a=0ll,b=0ll,c=0ll; cnt=0; cases++;

	gets(buf); gets(s);
	
	int i;
	for (i=0;s[i];i++) {
		char x=s[i];
		
		if (isalpha(x)) {
			add(toupper(x)-'A');
			
			if (cnt>=n) {
				if (calc()) {
					printf("%d\n",i); return ;
				}
			}
		}
	}
	
	printf("%d\n",i);
}

int main(){
	Pow[0]=1ll;
	for (int i=1;i<10;i++) Pow[i]=Pow[i-1]*51ll;
	
	cases=0;

	while (scanf("%d",&n)==1&&n) work();

	return 0;
}
