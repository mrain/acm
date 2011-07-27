#include <cstdio>
#include <cstring>
#include <sstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <cmath>

using namespace std;

#define maxn (1100)

string str[maxn][maxn];
int sum[maxn],len[maxn];
int n;

char buf[maxn];

int main() {
	int T; scanf("%d",&T); 
	gets(buf);
	
	while (T--) {
		n=0;
		int maxsum=0;
	
		while (gets(buf)) {
			if (buf[0]=='@'&&!buf[1]) break;
			
			n++; stringstream ss(buf);
			sum[n]=0;
			
			string tmp;
			while (ss >> tmp) str[n][++sum[n]]=tmp;		
			
			maxsum=max(maxsum,sum[n]);
		}
		
		for (int i=1;i<=maxsum;i++) {
			len[i]=0;
		
			for (int j=1;j<=n;j++) if (sum[j]>=i) 
				len[i]=max(len[i],(int)str[j][i].length());
		}
		
		for (int i=1;i<=n;i++) {
			for (int j=1;j<=sum[i];j++) {
				printf("%s",str[i][j].c_str());
				if (j<sum[i]) for (int a=0;a<=len[j]-str[i][j].length();a++) putchar(' ');
			}
			puts("");
		}
	}
}
