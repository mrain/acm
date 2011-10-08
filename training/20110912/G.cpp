#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<iostream>
#include<utility>
#define X first
#define Y second
using namespace std;
int n,rx[1003],ry[1003],Q[1003],cnt;
pair<int,int> p[1003];
vector<int> e[1003];
bool cmp1(int a,int b){
	return p[a].X==p[b].X?p[a].Y<p[b].Y:p[a].X<p[b].X;
}
bool cmp2(int a,int b){
	return p[a].Y==p[b].Y?p[a].X<p[b].X:p[a].Y<p[b].Y;
}
void DFS(int fa,int u){
	if(cnt&&u==0)return;
	Q[cnt++]=u;
	for(int i=0;i<e[u].size();++i){
		int v=e[u][i];
		if(v==fa)continue;
		DFS(u,v);
		break;
	}
}
long long area(){
	Q[cnt]=Q[0];
	long long ret=0;
	for(int i=0;i<cnt;++i)
		ret+=1LL*p[Q[i]].X*p[Q[i+1]].Y-1LL*p[Q[i+1]].X*p[Q[i]].Y;
	return ret;
}
int main(){
	while(scanf("%d",&n)==1&&n){
		if(n&1)return 1/0;
		for(int i=0;i<n;++i)
			scanf("%d%d",&p[i].X,&p[i].Y);
		for(int i=0;i<n;++i)
			rx[i]=ry[i]=i;
		stable_sort(rx,rx+n,cmp1);
		stable_sort(ry,ry+n,cmp2);
		for(int i=0;i<n;++i)e[i].clear();
		for(int i=0;i+1<n;i+=2){
			e[rx[i]].push_back(rx[i+1]);
			e[rx[i+1]].push_back(rx[i]);
			e[ry[i]].push_back(ry[i+1]);
			e[ry[i+1]].push_back(ry[i]);
		}
		cnt=0;
		DFS(-1,0);
		if(area()>0)reverse(Q,Q+cnt);
		rotate(Q,min_element(Q,Q+cnt),Q+cnt);
		Q[cnt]=Q[0];
		for(int i=0;i<cnt;++i)
			if(p[Q[i]].X==p[Q[i+1]].X)
				putchar(p[Q[i]].Y<=p[Q[i+1]].Y?'N':'S');
			else if(p[Q[i]].Y==p[Q[i+1]].Y)
				putchar(p[Q[i]].X<=p[Q[i+1]].X?'E':'W');
			else while(1);
		puts("");
	}
	return 0;
}
