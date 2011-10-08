#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int N,M,K,P,a[203];
bool vx[203],vy[203];
int lk[203],be[203];
long long slack[203],d[203][203],e[203][203],lx[203],ly[203];
/*
bool bfs(){
	while(!q.empty()){
		int p=q.front(),u=p>>1;q.pop();
		if(p&1){
			if(ym[u]==-1){
				while(u!=-1){
					ym[u]=prev[u];
					swap(xm[prev[u]],u);
				}
				return true;
			}else{
				q.push(ym[u]<<1);
				vx[ym[u]]=1;
			}
		}
		else{
			for(int i=1;i<=N;++i){
				if(vy[i])continue;
				if(lx[u]+ly[i]==e[u][i]){
					prev[i]=u;
					q.push((i<<1)|1);
					vy[i]=1;
				}
				else{
					long long ex=lx[u]+ly[i]-e[u][i];
					if(slack[i]>ex){
						slack[i]=ex;
						prev[i]=u;
					}
				}
			}
		}
	}
	return 0;
}*/
bool DFS(int u){
	vx[u]=1;
	for(int i=1;i<=N;++i){
		if(vy[i])continue;
		if(lx[u]+ly[i]==e[u][i]){
			vy[i]=1;
			if(lk[i]==-1||DFS(lk[i])){
				lk[i]=u;
				return 1;
			}
		}
		else slack[i]=min(slack[i],lx[u]+ly[i]-e[u][i]);
	}
	return 0;
}
int main(){
//	while(scanf("%d%d%d%d",&N,&M,&K,&P)==4){
	while (cin >> N >> M >> K >> P) {
		memset(be,0,sizeof(be));
		for(int i=1;i<=N;++i){
			//scanf("%d",a+i);
			cin >> a[i];
			be[a[i]]=i;
		}
		memset(d,63,sizeof(d));
		for(int i=1;i<=K;++i){
			int x,y;
			long long z;
			cin>>x>>y>>z;
			d[x][y]=min(d[x][y],z);
			d[y][x]=min(d[y][x],z);
		}

		for(int i=1;i<=M;++i)
			for(int j=1;j<=M;++j)
				for(int k=1;k<=M;++k)
					d[j][k]=min(d[j][k],d[j][i]+d[i][k]);
		for(int i=1;i<=M;++i)
			d[i][i]=0;
		memset(e,-63,sizeof(e));
		for(int i=1;i<=P;++i){
			int x,y;
			long long z;
			//scanf("%d%d%d",&x,&y,&z);
			cin >> x >> y >> z;
			for(int j=1;j<=M;++j)
				if(be[j])
					e[x][be[j]]=max(e[x][be[j]],-(z+d[y][j]));
		}
		for(int i=1;i<=N;++i){
			ly[i]=0;
			lx[i]=*max_element(e[i]+1,e[i]+N+1);
		}/*
		for(int i=1;i<=N;++i){
			for(int j=1;j<=N;++j)
				printf("%d ",e[i][j]);
			puts("");
		}*/
		memset(lk,-1,sizeof(lk));
		for(int idx=1;idx<=N;idx++){
			for(;;){
				memset(vx,0,sizeof(vx));
				memset(vy,0,sizeof(vy));
				memset(slack,63,sizeof(slack));
				if(1==DFS(idx))break;
				long long ex=(~0U>>1);
				for(int i=1;i<=N;++i)
					if(!vy[i])
						ex=min(ex,slack[i]);
				for(int i=1;i<=N;++i){
					if(vx[i])
						lx[i]-=ex;
					if(vy[i])
						ly[i]+=ex;
				}
			}
		}
		long long ans=0;
		for(int i=1;i<=N;++i)
			ans+=e[lk[i]][i];
		cout<<-ans<<endl;
	}
	return 0;
}
