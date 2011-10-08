#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int N,F,W,G,a[1003],g[1003];
long long rest[1003],chance[1003],mv[1003];
int main(){
	while(scanf("%d%d%d%d",&N,&F,&W,&G)==4){
		for(int i=1;i<=N;++i)
			scanf("%d%d",a+i,g+i);
		a[0]=0;
		for(int i=1;i<=N;++i)
			a[i]=max(a[i],a[i-1]);
		for(int i=N;i;--i){
			mv[i]=a[i];
			if(i!=N)mv[i]=max(mv[i],mv[i+1]-g[i]);
		}
		if(mv[1]>G){
			puts("It's useless to collect wood.");
			continue;
		}
		long long sum=0;
		g[0]=0;
		for(int i=0;i<=N;++i){
			G+=g[i];
			rest[i]=G-mv[i+1]-sum;
			sum+=rest[i];
		}
		G=0;
		for(int i=0;i<=N;++i){
			G+=rest[i];
			chance[i]=G/F;
			G%=F;
		}/*
		for(int i=1;i<=N;++i)
			cout<<rest[i]<<endl;*/
		long long x=W,y=0;
		long long ans=0;
		for(int i=0;i<=N;++i){
			ans+=1LL*x*y;
			if(chance[i]+y<x)
				y+=chance[i];
			else{
				int sum=chance[i]+x+y;
				x=(sum+1)/2;
				y=sum/2;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
