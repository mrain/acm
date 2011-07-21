#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

#define maxn (100)
#define MP make_pair
#define PB push_back
#define A first
#define B second

typedef pair<int,int> PII;

vector<PII> now;
char s[maxn][maxn];
string ans[maxn];
int sum;

const char G[7]="KQRBNP";

bool cmp1(PII a,PII b) {
	return a.A<b.A||a.A==b.A&&a.B<b.B;
}

bool cmp2(PII a,PII b) {
	return a.A>b.A||a.A==b.A&&a.B<b.B;
}

void work(int t){
	sum=0;

	for (int k=0;k<6;k++) {
		now.clear();
		for (int i=1;i<=8;i++)
			for (int j=1;j<=8;j++) {
				char x=s[17-i*2][j*4-2];
				
				if (t==-1&&G[k]==x||t==1&&x==tolower(G[k])) now.PB(MP(i,j));
			}
			
		if (t==-1) sort(now.begin(),now.end(),cmp1);
		else sort(now.begin(),now.end(),cmp2);
		
		for (int i=0;i<now.size();i++) {
			sum++;
			ans[sum]="";
			
			if (k!=5) ans[sum].PB(G[k]);
			
			ans[sum].PB('a'+now[i].B-1);
			ans[sum].PB('0'+now[i].A);
		}
	}
	
	if (t==-1) cout << "White: " ;
	else cout << "Black: " ;
	for (int i=1;i<sum;i++) cout << ans[i] << ',' ;
	cout << ans[sum] << endl ;
}

int main(){
	for (int i=0;i<17;i++) scanf("%s",s[i]);
	
	work(-1),work(1);

	return 0;
}
