#include <cstdio>
#include <set>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (20000)
#define MP make_pair
#define A first
#define B second

typedef pair<int,int> PII;

char s[100];
PII req[maxn];
multiset<PII> f;
int n,m;

multiset<PII>::iterator it;

int main(){
	while (scanf("%s",s)==1&&s[0]!='#') {
		int x,y; scanf("%d%d",&y,&x);
		req[n++]=MP(x,y);
	}
	
	sort(req,req+n);
	
	scanf("%d",&m);
	for (int i=0;i<n;i++) {
		int prd=req[i].A,idx=req[i].B;
		
		for (int j=1;j<=m;j++) {
			f.insert(MP(prd*j,idx));
			
			if (f.size()>m) {
				it=f.end(); it--;
				bool flag=false;
				if (it->B==idx) flag=true;
				f.erase(it);
				if (flag) break;
			}
		}
	}
	
	for (it=f.begin();it!=f.end();it++) printf("%d\n",it->B);

	return 0;
}
