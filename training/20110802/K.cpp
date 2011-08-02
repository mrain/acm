#include<cstdio>
#include<map>
#include<utility>
#include<iostream>
#include<cstring>
#define mp make_pair
using namespace std;
map<int,int> num;
//map< pair< pair<int,int>,int > ,int> h;
int h[120][120][120];
const int seg[]={6,2,5,5,4,5,6,3,7,6};
int calc(int x)
{
	int ret=0;
	if(x==0)return seg[0];
	if(x<0)++ret,x*=-1;
	while(x)
	{
		ret+=seg[x%10];
		x/=10;
	}
	return ret;
}
int main()
{
//	num.clear();
	memset(h, 0, sizeof(h));
	for(int i=-999;i<=999;++i)
		num[i]=calc(i)*5;
	for(int i=-999;i<=999;++i)
		for(int j=-999;j<=999;++j)
			if(i+j>=-999&&i+j<=999)
				++ h[num[i]][num[j]][num[i+j]];
	for(int i=-999;i<=999;++i)
		for(int j=-999;j<=999;++j)
			if(i-j>=-999&&i-j<=999)
				++ h[num[i]][num[j]][num[i-j]];
//				++h[mp(mp(num[i],num[j]),num[i-j])];
	for(int i=-999;i<=999;++i)
		for(int j=-999;j<=999;++j)
			if(i*j>=-999&&i*j<=999)
				++ h[num[i]][num[j]][num[i*j]];
				//++h[mp(mp(num[i],num[j]),num[i*j])];
	for(int i=-999;i<=999;++i)
		for(int j=-999;j<=999;++j)
			if(j!=0&&i/j>=-999&&i/j<=999/*&&i%j==0*/)
				++ h[num[i]][num[j]][num[i/j]];
//				++h[mp(mp(num[i],num[j]),num[i/j])];
	int x,y,z;
	while(scanf("%d",&x),x)
	{
		scanf("%d%d",&y,&z);
		int ans = h[x][y][z];
		printf("%d %s for %d %d %d\n",ans,(ans==1?"solution":"solutions"),x,y,z);
	}		
	return 0;
}
