#include <cstdio>
#include <string>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <cmath>
#include <map>

using namespace std;

#define maxn (10000)

char buf[maxn];
string cmds[maxn];
map<int,int> f[100]; 
int size[100];

int s2d(const string& str) {
	int ret;
	stringstream ss(str); ss >> ret ;
	return ret;
}

int arr(char x) {
	if (x<='Z') return x-'A';
	return x-'a'+26;
}

int calc(const string& str) {
	if (isdigit(str[0])) return s2d(str);
	
	int index=arr(str[0]);
	int x=calc(str.substr(2,str.length()-3));
	
	if (x==-1||x>=size[index]||f[index].find(x)==f[index].end()) return -1;
	
	return f[index][x];
}

bool put(const string& str,int v) {
	int index=arr(str[0]);
	int x=calc(str.substr(2,str.length()-3));
	
	if (x==-1||x>=size[index]||v==-1) return false;
	
	f[index][x]=v; return true;
}

int main() {

	while (scanf("%s",buf)==1) {
		int N=0,ans=0;
		
		memset(size,0,sizeof(size));
		for (int i=0;i<52;i++) f[i].clear();
		
		while (buf[0]!='.') {
			cmds[N++]=string(buf);
			scanf("%s",buf);
		}
		 
		for (int t=0;t<N;t++) {
			string str=cmds[t];
		
			int pos=-1;
			for (int i=0;i<str.size();i++) {
				if (str[i]=='=') {
					pos=i; break;
				}
			}
			
			if (pos!=-1) {
				if (!put(str.substr(0,pos),calc(str.substr(pos+1)))) {
					if (!ans) {
						ans=t+1;
					}
				}
			}
			else {
				int index=arr(str[0]);
				int s=calc(str.substr(2,str.length()-3));
				
				if (s==-1) {
					if (!ans) {
						ans=t+1;
					}
				}
				else size[index]=s;
			}
		}
		
		printf("%d\n",ans);
	}

	return 0;
}
