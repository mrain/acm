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

struct Map{
	short a[8000000];
	
	Map() {
		clear();
	}
	
	void clear() {
		memset(a,-1,sizeof(a));
	}
	
	bool put(int v,int x) {
		if (a[v]!=-1) return false;
		
		a[v]=x; return true;
	}
	
	int get(int v) {
		return a[v];
	}
}f[2];

queue<int> q[2];
int m,n,s;
int st[5],ed[5],pos[5],dir[5],to[5],bound[5];
int ST,ED,tot;
int mark[20][20];
int d[1000][5];

const int dx[5]={0,-1,0,0,1},dy[5]={0,0,-1,1,0};

string buf;

int A[4];

void init() {
	memset(d,-1,sizeof(d));

	getline(cin,buf); tot=0;
	
	for (int i=0;i<m;i++) {
		getline(cin,buf);
		
		for (int j=0;j<n;j++) {
			char x=buf[j];
			
			if (x!='#') mark[i][j]=tot++;
			else mark[i][j]=-1;
			
			if (isalpha(x)) {
				if (isupper(x)) {
					st[x-'A']=tot-1;			
				}
				else {
					ed[x-'a']=tot-1;
				} 
			}
		}
	}
	
	for (int i=0;i<m;i++)
		for (int j=0;j<n;j++) if (mark[i][j]!=-1) {
			for (int a=0;a<5;a++) {
				int x=i+dx[a],y=j+dy[a];
				d[mark[i][j]][a]=mark[x][y];
				
				//printf("%d %d\n",mark[i][j],mark[x][y]);
			}
		}
	
	//cout << tot << endl ;
	
	A[0]=1; A[1]=tot; A[2]=tot*tot;A[3]=tot*tot*tot;
	
	ST=ED=0;
	for (int i=0;i<s;i++) ST+=st[i]*A[i];
	for (int i=0;i<s;i++) ED+=ed[i]*A[i];
}

void relax(queue<int>& q,Map& f) {
	//while (!q.empty()) {
		int V=q.front(); q.pop();
		int D=f.get(V);
		
		cout << V << "-->" ;
		for (int i=0;i<s;i++) {
			pos[i] = (V % A[i+1]) / A[i];
		}
		
		printf("%d %d %d : %d\n",pos[0],pos[1],pos[2],D);
		
		for (int i=0;i<3;i++) if (i<s) bound[i]=5; else bound[i]=1;
		
		for (dir[0]=0;dir[0]<bound[0];dir[0]++) { 
			for (dir[1]=0;dir[1]<bound[1];dir[1]++) {
				for (dir[2]=0;dir[2]<bound[2];dir[2]++) {
					
					printf("%d %d %d\n",to[0],to[1],to[2]);
					
					for (int i=0;i<s;i++) to[i]=d[pos[i]][dir[i]];
					
					bool ok=true;
					
					for (int i=0;i<s&&ok;i++) if (to[i]==-1) ok=false;
					
					for (int i=0;i<s&&ok;i++)
						for (int j=i+1;j<s&&ok;j++) {
							if (to[i]==to[j]) ok=false;
							if (to[i]==pos[j]&&to[j]==pos[i]&&dir[i]+dir[j]==4) ok=false;
						}
						
					if (!ok) continue;
						
					int v=0;
					for (int i=0;i<s;i++) v+=to[i]*A[i];
					
					if (f.put(v,D+1)) q.push(v);
				}
			}
		}
	//}	
}

void work() {
	f[0].clear(),f[1].clear();
	//HashMap f[2];
	while (!q[0].empty()) q[0].pop();
	while (!q[1].empty()) q[1].pop();
	
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
