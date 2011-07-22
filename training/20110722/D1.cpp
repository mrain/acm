#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

#define maxn (110000)

double A[maxn],F[maxn];
int n,p,a,b;
double P,Q;

int main(){
	
	while (scanf("%d%d%d%d",&n,&p,&a,&b)==4&&(n+p+a+b)) {
		P=((double) p)/100.; Q=1.-P;
		
		A[n+1]=F[n+1]=0.;
		
		for (int i=n;i>0;i--) {
			F[i]=Q*F[i+1]+P*A[i+1]; A[i]=min(F[i]+((double) a),A[i+1]+((double) b));
		}
		
		printf("%f\n",F[1]);
	}

	return 0;
}
