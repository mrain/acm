#include<set>
#include<cstdio>
#include<vector>
#include<utility>
#include<cstring>
#include<algorithm>
#define pb push_back
#define mp make_pair
#define A first
#define B second
using namespace std;
typedef pair<int,int> PII;
bool cmp(const PII &a,const PII &b){
	if(a.B!=b.B)return a.B<b.B;
	else return a.A>b.A;
}
int calc(int u,vector<PII> h){
	for(int i=0;i<h.size();++i)
		swap(h[i].A,h[i].B);
	stable_sort(h.begin(),h.end(),cmp);
	int i;
	for(i=0;i<h.size();++i)
		if(h[i].A>1)
			break;
	if(i==h.size()){
		int ret=0;
		for(int i=0;i<h.size();++i)
			ret+=h[i].B-1;
		return ret;
	}
	PII tmp=h[i];
	h.erase(h.begin()+i);
	h.push_back(mp(tmp.A/2,tmp.B));
	h.push_back(mp(tmp.A-tmp.A/2,tmp.B));
	return calc(u^1,h);
}
int main(){
	for(int i=1;i<=20;++i){
		for(int j=1;j<=20;++j){
			vector<PII> h;
			h.pb(mp(j,i));
			printf("%d ",calc(1,h));
		}
		puts("");
	}/*
	vector<PII> h;
	h.pb(mp(1000,1000));
	printf("%d\n",calc(1,h));*/
	return 0;
}
