#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <set>

using namespace std;

set<string> f;
string name[100];
char buf[1000];
int n,m;

int main() {
	int T; scanf("%d",&T);
	
	for (int t=1;t<=T;t++) {
		printf("Test set %d:\n",t);
	
		scanf("%d",&n);
		for (int i=1;i<=n;i++) cin >> name[i] ;
		
		scanf("%d",&m);
		f.clear(); gets(buf);
		for (int i=0;i<m;i++) {
			gets(buf); stringstream ss(buf);
			
			string str;
			
			while (ss >> str) f.insert(str);
		}
		
		for (int i=1;i<=n;i++) {
			printf("%s is ",name[i].c_str());
			
			if (f.find(name[i])!=f.end()) puts("present");
			else puts("absent");
		}
	
		puts("");
	}	
	

	return 0;
}
