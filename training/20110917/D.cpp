#include<cstdio>
#include<string>
#include<utility>
#include<map>
#include<iostream>
#include<cstring>
using namespace std;
const int N=34003;
map< pair<string,string> ,int> h;
int p,n;

int sz,ed[N];
struct edge{
	int y,v,nt;
	edge(){}
	edge(int y,int v,int nt):y(y),v(v),nt(nt){}
}e[3000003];
void addEdge(int x,int y,int v){
	//printf("%d %d %d\n",x,y,v);
	e[++sz]=edge(y,v,ed[x]);
	ed[x]=sz;
}

int d[N],Q[N];
bool inQ[N];
void SPFA(int u){
	int l=0,r=1;
	Q[l]=u;
	memset(d,-1,sizeof(d));
	d[u]=0;inQ[u]=1;
	while(l!=r){
		int x=Q[l];
		++l;inQ[x]=0;
		if(l==N)l=0;
		for(int i=ed[x];i;i=e[i].nt){
			int y=e[i].y;
			if(d[y]==-1||d[y]>d[x]+e[i].v){
				d[y]=d[x]+e[i].v;
				if(!inQ[y]){
					Q[r]=y;
					if(l!=r&&d[Q[r]]<d[Q[l]])
						swap(Q[l],Q[r]);
					++r;
					if(r==N)r=0;
					inQ[y]=1;
				}
			}
		}
	}
}

int main(){
	int cas=0;
	while(scanf("%d%d",&p,&n)==2&&p&&n){
		h.clear();
		memset(ed,0,sizeof(ed));
		sz=0;
		int cnt=0;
		for(int i=1;i<=p;++i){
			int k;
			scanf("%d",&k);
			string s1,s2;
			for(;;){
				cin>>s1>>s2;
				//cout<<s1<<" "<<s2<<endl;
				char c1=s1[s1.size()-1];
				char c2=s2[s2.size()-1];
				s1.erase(s1.end()-1);
				s2.erase(s2.end()-1);
				
				pair<string,string> hh=make_pair(s1,s2);
				int x;
				if(h.count(hh))x=h[hh];
				else x=h[hh]=++cnt;
				
				addEdge(p+x,i,0);
				addEdge(i,p+x,k);
				
				if(c2==':'){
					getline(cin,s1);
					break;
				}
			}
			//cout<<endl;
		}
		string x="Kevin";
		string y="Bacon";
		int id=h[make_pair(x,y)];
		SPFA(id+p);
		cout<<"Database "<<++cas<<endl;
		for(int i=1;i<=n;++i){
			string s1,s2;
			cin>>s1>>s2;
			s1.erase(s1.end()-1);
			int x=h[make_pair(s1,s2)]+p;
			cout<<s1<<", "<<s2<<": ";
			if(d[x]==-1)cout<<"infinity"<<endl;
			else cout<<d[x]<<endl;
		}
		cout<<endl;
	}
	return 0;
}
