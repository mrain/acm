#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <set>

using namespace std;

char s[1000];
set<char> f;
int g[1000],r[1000];
int now,cnt,flag,ans;

int calc() {
	if (flag) return -1;

	if (!s[now]) {
		flag=4; return -1;
	}

	char x=s[now++];
	
	if (islower(x)) return g[x-'a'];
	
	if (x=='A') return calc()|calc();
	if (x=='C') return (calc()==0)|calc();
	if (x=='D') return (calc()&calc())==0;
	if (x=='E') return calc()==calc();
	if (x=='J') return calc()^calc();
	if (x=='K') return calc()&calc();
	if (x=='N') return 1^calc();
 	
	flag=3; return -1;
}

void dfs(int x) {
	if (flag) return ;

	if (x>cnt) {
		now=0; 
		int x=calc();
		if (flag) return ;
		
		if (s[now]) flag=2;
		
		if (ans==-1) ans=x;
		else {
			if (ans!=x) flag=1;
		}
		
		return ;
	}
	
	g[r[x]]=0; dfs(x+1);
	g[r[x]]=1; dfs(x+1);
}

int main(){
	while (scanf("%s",s)==1) {
		f.clear(); cnt=0;
		for (int i=0;s[i];i++) if (islower(s[i])&&f.find(s[i])==f.end()) r[++cnt]=s[i]-'a',f.insert(s[i]);
		
		flag=0; ans=-1;
		dfs(1);
		
		switch (flag) {
			case 0: {
				if (ans==0) printf("%s is valid: contradiction\n",s);
				else printf("%s is valid: tautology\n",s);
				
				break;
			}
		
			case 1:	printf("%s is valid: contingent\n",s); break;
			case 2: printf("%s is invalid: extraneous text\n",s); break;
			case 3: printf("%s is invalid: invalid character\n",s); break;
			case 4: printf("%s is invalid: insufficient operands\n",s); break;
		}
	}

	return 0;
}
/*
q is valid: contingent
Cp is invalid: insufficient operands
Cpq is valid: contingent
A01 is invalid: invalid character
Cpqr is invalid: extraneous text
ANpp is valid: tautology
KNpp is valid: contradiction
Qad is invalid: invalid character
CKNppq is valid: tautology
JDpqANpNq is valid: contradiction
CDpwANpNq is valid: contingent
EDpqANpNq is valid: tautology
KCDpqANpNqCANpNqDpq is valid: tautology
*/
