#include<cstdio>
#include<cstring>
#include<utility>
#include<iostream>
#include<algorithm>
#define A first
#define B second
#define lowbit(x) (x&(-x))
using namespace std;

bool cnt[100003];
int n,m,d,pos[100003],l2[100003];
pair<int,int> h[100003];

int f[19][100003];

int query(int x,int y){
	int p=l2[y-x+1];
	return max(f[p][x],f[p][y-(1<<p)+1]);
}

int main(){
	l2[0]=-1;
	for(int i=1;i<100003;++i)
		l2[i]=l2[i-1]+(lowbit(i)==i ? 1 : 0);

	scanf("%d%d%d",&n,&m,&d);
	
	for(int i=1;i<=n;++i)
		scanf("%d%d",&h[i].A,&h[i].B);
	stable_sort(h+1,h+n+1);
	
	for(int i=1;i<=n;++i)pos[i]=h[i].A;
	
	for(int i=1;i<=n;){
		int ii=i,vv=0;
		while(ii!=n&&h[ii+1].A-h[ii].A<=d)++ii;
		for(int j=i;j<=ii;++j){
			if(!cnt[h[j].B])++vv;
			cnt[h[j].B]=1;
		}
		for(int j=i;j<=ii;++j)
			cnt[h[j].B]=0;
		for(int j=i;j<=ii;++j){
			f[0][j]=vv;
			//printf("%d\n",vv);
		}
		i=ii+1;
	}
	
	for(int i=1;i<19;++i)
		for(int j=1;j+(1<<i)-1<=n;++j)
			f[i][j]=max(f[i-1][j],f[i-1][j+(1<<i-1)]);
			
	int q;
	for(scanf("%d",&q);q--;){
		int x,y;
		scanf("%d%d",&x,&y);
		if(x<=pos[n])x=lower_bound(pos+1,pos+n+1,x)-pos;
		else x=n+1;
		
		if(y<pos[n])y=upper_bound(pos+1,pos+n+1,y)-pos-1;
		else if(y==pos[n])y=n;
		else y=n+1;
		
		//printf("%d %d\n",x,y);
		
		if(x>y||x>n||y<1)puts("0");
		else printf("%d\n",query(max(1,x),min(y,n)));
	}
	return 0;
}
