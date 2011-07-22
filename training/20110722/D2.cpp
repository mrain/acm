#include<cstdio>
#include<cmath>
#include<algorithm>

using namespace std;

int n,A,B;
double P,N;

double calc(double x) {
	double S=(pow(1.-P,x+1.)-(1.-P))/P+x;
	return S/x;
}

double work() {
	int l=1,r=n;
	
	while(l+100<r) {
		int k1=(l+r)>>1;
		int k2=(r+k1)>>1;
		if(calc((double) k1)<calc((double) k2))l=k1;
		else r=k2;
	}
	
	double x=calc(l); int pos=l;
	
	for(int i=l+1;i<=r;++i) {
		double tmp=calc(i);
		
		if (tmp<x) x=tmp,pos=i;		
	}
	
	double ret; N=(double) n;
	
	if (x>=P*A) ret=(())
	
	return ret;
}

int main() {
	int p;
	while (scanf("%d%d%d%d",&n,&p,&A,&B),n||p||A||B) {
		n--;
		
		P=p/100.0;
		
		printf("%.10f\n",work());
	}
	
	return 0;
}
