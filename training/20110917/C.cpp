#include<cstdio>
#include<utility>
#include<cstring>
#include<queue>
#include<algorithm>
#define make_pair MP
using namespace std;

const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};
const int opp[]={2,3,0,1};

typedef pair<int,int> pii;
typedef pair<pii,pii> PII;
typedef pair<PII,int> st;

int n,m,Ax,Ay,Bx,By;
char s[13][13];
pii pos[1000003];
queue<st> Q;

int findDirec(char ch){
	if(ch=='E')return 0;
	if(ch=='S')return 1;
	if(ch=='W')return 2;
	if(ch=='N')return 3;
}

int main(){
	while(scanf("%d%d",&n,&m)==2){
		for(int i=0;i<n;++i)
			scanf("%s",s[i]);
			
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j){
				if(s[i][j]=='A')
					Ax=i,Ay=j;
				if(s[i][j]=='B')
					Bx=i,By=j;
				if(s[i][j]=='K')
					pos[0]=make_pair(i,j);
			}
		s[Ax][Ay]='*';
		s[Bx][By]='*';
		
		char direc[3];
		scanf("%s",direc);
		int d=findDirec(direc[0]);
		for(int i=1;i<=1000000;++i){
			pii p=pos[i-1];
			p.X+=dx[d];
			p.Y+=dy[d];
			if(!inBoard(p)){
				p.X-=dx[d]*2;
				p.Y-=dy[d]*2;
			}
			pos[i]=p;
		}
		
		Q.push(MP(MP(MP(Ax,Ay),MP(Bx,By))),0);
		while(!Q.empty()){
			PII x=Q.front();
			pii x=x.X.X;
			pii y=x.X.Y;
			int v=x.Y;
			for(int i=0;i<4;++i){
				pii xx=x,yy=y;
				xx.X+=dx[i];
				xx.Y+=dy[i];
				yy.X+=dx[op[i]];
				yy.Y+=dy[op[i]];
				
				if(inBoard(xx)&&inBoard(yy))
			}
		}
	}
	return 0;
}
