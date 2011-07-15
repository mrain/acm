#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

double h1,h2,d1,d2,a,b;

void equation(double A,double B,double C,double& x1,double& x2) {
	double delta=B*B-4.*A*C;
	x1=x2=-1;
/*	
	printf("%lf %lf %lf\n",A,B,C);
	printf("Delta %lf\n",delta);
*/	
	if (delta<0.) return ;
	
	if (A==0.) {
		if (B==0.) return ;
		
		x1=-C/B; return ;
	}
	
	x1=(-B+sqrt(delta))*0.5/A,x2=(-B-sqrt(delta))*0.5/A;
}	

bool ok(double x) {
	double h;

	if (x>=0.&&x<=d1) {
		double y=b*(d2-x)*(d2-x);
		
		h=y-b*(d1-x)*(d1-x);
	}
	else {
		if ((x>d2||x<0.)&&h1!=d2*d2*a) return false;
	
		h=h1-a*d1*d1;
	}
/*	
	printf("%lf: %lf\n",x,h);
*/
	return h>=h2;
}

int main(){
	
	while (scanf("%lf%lf%lf%lf%lf%lf",&h1,&h2,&d1,&d2,&a,&b)==6) {
		double x1,x2;
		double A=a+b;
		double B=-2.*b*d2;
		double C=b*d2*d2-h1;
		
		equation(A,B,C,x1,x2);
/*		
		printf("%lf %lf\n",x1,x2);
*/	
		if (ok(x1)||ok(x2)) puts("Yes");
		else puts("No");
	}

	return 0;
}
