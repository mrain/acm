#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <cctype> 
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

#define maxn (500000)
#define PB push_back

const int length=(1<<18)-1;

struct HashMap{
	vector<int> a[maxn];
	vector<short> b[maxn];
	
	HashMap() {
	clear();
	}
	
	void clear() {
		for (int i=0;i<=length;i++) 
			a[i].clear(),b[i].clear();
	}
	
	int hash(int h) {
		h^=(h>>20)^(h>>12); h^=(h>>7)^(h>>4);
		return h&length;
	}
	
	bool put(int v,int x) {
		int index=hash(v);
		
		for (int i=0;i<a[index].size();i++) if (a[index][i]==v) return false;
		
		a[index].PB(v),b[index].PB(x);
		return true;
	}
	
	int get(int v) {
		int index=hash(v);
		
		for (int i=0;i<a[index].size();i++) if (a[index][i]==v) return b[index][i];
		
		return -1;
	}
}f[2];

queue<int> q[2];
int m,n,s;
int st[5],ed[5],pos[5],dir[5],to[5],d[5],bound[5];
int ST,ED;
bool flag[1000];

string buf;

const int A[3]={(1<<8)-1,(1<<16)-(1<<8),(1<<24)-(1<<16)};
const int B[3]={1,1<<8,1<<16};

void init() {
	memset(flag,0,sizeof(flag));

	getline(cin,buf);
	for (int i=0;i<m;i++) {
		getline(cin,buf);
		
		for (int j=0;j<n;j++) {
			char x=buf[j];
			if (isalpha(x)) {
				if (isupper(x)) {
					st[x-'A']=i*n+j;			
				}
				else {
					ed[x-'a']=i*n+j;
				} 
			}
			else {
				if (x=='#') flag[i*n+j]=true;
			}
		}
	}
	
	ST=ED=0;
	for (int i=0;i<s;i++) ST+=(st[i]<<(i<<3));
	for (int i=0;i<s;i++) ED+=(ed[i]<<(i<<3));
}

void relax(queue<int>& q,HashMap& f) {
	//while (!q.empty()) {
		int V=q.front(); q.pop();
		int D=f.get(V);
		
		for (int i=0;i<s;i++) pos[i]=(V&A[i])>>(i<<3);
		
		//printf("%d %d %d : %d\n",pos[0],pos[1],pos[2],D);
		
		for (int i=0;i<3;i++) if (i<s) bound[i]=5; else bound[i]=1;
		
		for (dir[0]=0;dir[0]<bound[0];dir[0]++)
			for (dir[1]=0;dir[1]<bound[1];dir[1]++)
				for (dir[2]=0;dir[2]<bound[2];dir[2]++) {
					for (int i=0;i<s;i++) to[i]=pos[i]+d[dir[i]];
					
					bool ok=true;
					
					for (int i=0;i<s&&ok;i++) if (flag[to[i]]) ok=false;
					
					for (int i=0;i<s&&ok;i++)
						for (int j=i+1;j<s&&ok;j++) {
							if (to[i]==to[j]) ok=false;
							if (to[i]==pos[j]&&to[j]==pos[i]&&dir[i]+dir[j]==3) ok=false;
						}
						
					if (!ok) continue;
						
					int v=0;
					for (int i=0;i<s;i++) v+=to[i]<<(i<<3);
					
					if (f.put(v,D+1)) q.push(v);
				}
	//}	
}

void work() {
	f[0].clear(),f[1].clear();
	//HashMap f[2];
	while (!q[0].empty()) q[0].pop();
	while (!q[1].empty()) q[1].pop();

	d[0]=-1,d[1]=-n,d[2]=n,d[3]=1,d[4]=0;
	
	f[0].put(ST,0),q[0].push(ST);
	f[1].put(ED,0),q[1].push(ED);
	
	while (!q[0].empty()&&!q[1].empty()) {
		if (q[0].size()>q[1].size()) {
			int v=q[1].front(); int d1=f[0].get(v),d2=f[1].get(v);
			
			if (d1!=-1&&d2!=-1) {
				printf("%d\n",d1+d2); break;
			}
		
			relax(q[1],f[1]);
		}
		else {
			int v=q[0].front(); int d1=f[0].get(v),d2=f[1].get(v);
			
			if (d1!=-1&&d2!=-1) {
				printf("%d\n",d1+d2); break;
			}
		
			relax(q[0],f[0]);
		}
		//printf("%d %d\n", q[0].size(), q[1].size());
	}
}

int main(){
	
	while ((cin >> n >> m >> s)&&(n||m||s)) {
		init(); work();
	}

	return 0;
}
