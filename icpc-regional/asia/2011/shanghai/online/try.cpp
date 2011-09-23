#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main(){
	int cnt=0;
	for(int i=1;i<=5;++i)
		for(int j=1;j<=5;++j)
			if(__gcd(i,j)==1)
				++cnt;
	printf("%d\n",cnt);
	return 0;
}
