#include<cstdio>
#include<set>
#include<queue>
#include<cstring>
#include<utility>
#include<iostream>
#include<algorithm>
#define MP make_pair
#define lowbit(x) ((x)&(-(x)))
using namespace std;
int n,l,con[1031],cnt;
char s[103];
typedef pair<int,int> PII;
queue<PII> h[2];
int vis[1031][1031], times;

struct node{
	int v,suffix;
	int nt[4];
	node(){}
	void init(){
		v=suffix=nt[0]=nt[1]=nt[2]=nt[3]=0;
	}
};
node T[1003];

int getNum(char ch){
	switch(ch){
		case 'A':return 0;
		case 'G':return 1;
		case 'T':return 2;
		case 'C':return 3;
	}
}

void insertTree(int x){
	int p=0,len=strlen(s);
	for(int i=0;i<len;++i){
		int v=getNum(s[i]);
		if(T[p].nt[v])p=T[p].nt[v];
		else{
			++cnt;
			T[cnt].init();
			T[p].nt[v]=cnt;
			p=cnt;
		}
	}
	T[p].v|=(1<<x-1);
}

queue<int> q;
void getSuffix(){
	q.push(0);
	while(!q.empty()){
		int x=q.front();
		T[x].v|=T[T[x].suffix].v;
		q.pop();
		for(int i=0;i<4;++i)
			if(T[x].nt[i]){
				int y=T[x].nt[i];
				if(x==0)T[y].suffix=0;
				else T[y].suffix=T[T[x].suffix].nt[i];
				q.push(y);
			}
			else
				T[x].nt[i]=T[T[x].suffix].nt[i];
	}
}

int step(int u,int v){
	return T[u].nt[v];
}

int main(){
	times = 0;
	memset(vis, 0, sizeof(vis));
	while(scanf("%d%d",&n,&l)==2){
		cnt=0;
		T[0].init();
		memset(con,0,sizeof(con));
		for(int i=1;i<=n;++i){
			scanf("%s%d",s,&con[(1<<i-1)]);
			insertTree(i);
		}
		for(int i=1;i<(1<<n);++i){
			int j=lowbit(i);
			con[i]=con[j]+con[i-j];
		}
		getSuffix();
		
		//h[0].clear();
		while (!h[0].empty()) h[0].pop();
		h[0].push(MP(0,0));
		int ans=-100000;
		for(int i=1;i<=l;++i){
			int u=(i&1); ++ times;
			//h[u].clear();
			while (!h[u].empty()) h[u].pop();
//			for(set<PII>::iterator it=h[u^1].begin();it!=h[u^1].end();++it){
			while (!h[u ^ 1].empty()) {
				int pos=h[u ^ 1].front().first;
				int mask=h[u ^ 1].front().second;
				h[u ^ 1].pop();
				for(int i=0;i<4;++i){
					int ppos=step(pos,i);
					int mmask=mask|T[ppos].v;
					if(mmask!=(1<<n)-1){
						if (vis[ppos][mmask] == times) continue;
						vis[ppos][mmask] = times;
						PII now=MP(ppos,mmask);
						/*if(h[u].find(now)==h[u].end())
							h[u].insert(now);*/
						h[u].push(now);
					}
					else ans=max(ans,con[mmask]);
				}	
			}
		}
		/*for(set<PII>::iterator it=h[(l&1)].begin();it!=h[(l&1)].end();++it){
			//if(it->second==0)continue;
			ans=max(ans,con[it->second]);
			//printf("%d %d %d\n",it->first,it->second, con[it->second]);
		}*/
		while (!h[l & 1].empty()) {
			ans = max(ans, con[h[l & 1].front().second]);
			h[l & 1].pop();
		}
		if(ans<0)puts("No Rabbit after 2012!");
		else printf("%d\n",ans);
	}
	return 0;
}
