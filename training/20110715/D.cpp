#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (100) 
#define MP make_pair
#define A first
#define B second

typedef pair<int,int> PII;

PII pos[maxn],g[maxn];
int sum[maxn],now[maxn],cnt[maxn];
bool flag[maxn];
char s[maxn][maxn];

const int n=12,m=26;

void add(int x,int a,int b,int c,int d) {
	pos[x]=MP(a,b),g[x]=MP(c,d);
}

inline bool check() {
	for (int i=1;i<=6;i++) if (sum[i]!=m) return false;
	
	return true;
}

bool dfs(int x) {
	if (x>n) {
		return true;
	}
	
	if (now[x]) return dfs(x+1);
	
	for (int i=1;i<=n;i++) if (!flag[i]) {
		now[x]=i,flag[i]=true,sum[g[x].A]+=i,sum[g[x].B]+=i,cnt[g[x].A]++,cnt[g[x].B]++;
		if (!(cnt[g[x].A] == 4 && sum[g[x].A] != m)) 
			if (!(cnt[g[x].B] == 4 && sum[g[x].B] != m)) 
				if (sum[g[x].A]<=26&&sum[g[x].B]<=26&&dfs(x+1)) return true;
 		
		now[x]=0,flag[i]=false,sum[g[x].A]-=i,sum[g[x].B]-=i,cnt[g[x].A]--,cnt[g[x].B]--;
	}
	
	return false;
}

int main(){
	add(1,0,4,1,3);
	add(2,1,1,4,6);
	add(3,1,3,1,4);
	add(4,1,5,3,4);
	add(5,1,7,4,5);
	add(6,2,2,1,6);
	add(7,2,6,3,5);
	add(8,3,1,1,2);
	add(9,3,3,2,6);
	add(10,3,5,2,5);
	add(11,3,7,2,3);
	add(12,4,4,5,6);

	for (int i=0;i<5;i++)
		scanf("%s",s[i]);
		
	for (int i=1;i<=n;i++) if (s[pos[i].A][pos[i].B]!='x') {
		int x=s[pos[i].A][pos[i].B]-'A'+1;
		flag[x]=true,now[i]=x;
		sum[g[i].A]+=x,sum[g[i].B]+=x,cnt[g[i].A]++,cnt[g[i].B]++;
	}
	
	dfs(1);
	
	for (int i=1;i<=n;i++) s[pos[i].A][pos[i].B]='A'+now[i]-1;
	
	for (int i=0;i<5;i++) puts(s[i]);

	return 0;
}
