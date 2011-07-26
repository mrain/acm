#include <algorithm>
#include <cstring>
#include <cctype> 
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

#define A first
#define B second
#define MP make_pair 

map<int,int> dis;
queue<int> q;
int m,n,s;
int st[5],ed[5],pos[5],d[5];
int ST,ED;
bool flag[1000];

char buf[100];

const int A1=(1<<8)-1,A2=(1<<16)-(1<<8),A3=(1<<24)-(1<<16);
const int B1=1,B2=1<<8,B3=1<<16;

void init() {
	memset(flag,0,sizeof(flag));

	gets(buf);
	for (int i=0;i<m;i++) {
		gets(buf);
		
		for (int j=0;j<n;j++) {
			char x=buf[j];
			if (isalpha(x)) {
				if (isupper(x)) {
					st[x-'A'+1]=i*n+j;			
				}
				else {
					ed[x-'a'+1]=i*n+j;
				} 
			}
			else {
				if (x=='#') flag[i*n+j]=true;
			}
		}
	}
	
	ST=st[1]+st[2]*B2+st[3]*B3,ED=ed[1]+ed[2]*B2+ed[3]*B3;
}

void work() {
	d[0]=-1,d[1]=1,d[2]=-n,d[3]=n;

	while (!q.empty()) q.pop(); dis.clear();
	
	dis[ST]=0,q.push(ST);
	
	while (!q.empty()) {
		int V=q.front(); q.pop();
		if (V==ED) {
			printf("%d\n",dis[ED]); break;
		}
		
		pos[1]=V&A1,pos[2]=(V&A2)>>8,pos[3]=(V&A3)>>16;
		
		int D=dis[V];
		//printf("%d %d %d : %d\n",pos[1],pos[2],pos[3],D);
		
		for (int k=1;k<=s;k++) {
			for (int i=0;i<4;i++) {
				int x=d[i]+pos[k];
				
				if (flag[x]) continue;
				
				bool cov=false;
				for (int j=1;j<=s;j++) if (j!=k) {
					if (pos[j]==x) { 
						cov=true; break;
					}
				}
				
				if (cov) continue;
				
				//int v=pos[1]+pos[2]*B2+pos[3]*B3;
				int v = V + (d[i] << (8 * (k - 1)));
				
				if (dis.find(v)!=dis.end()) continue;
				
				dis[v]=D+1,q.push(v);
			}
		}
	}
}

int main(){
	
	while (scanf("%d%d%d",&n,&m,&s)==3&&(n||m||s)) {
		init(); work();
	}

	return 0;
}
