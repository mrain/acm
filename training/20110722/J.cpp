#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const double pi=acos(-1.);
const double a[3]={2.*pi/43200.,2.*pi/3600.,2.*pi/60.};
double l[3],m[3];
int st,ed;

bool work() {
	for (int i=0;i<3;i++) {
		scanf("%lf",&l[i]);
		if (l[i]<0.) return false;
	}

	for (int i=0;i<3;i++) {
		scanf("%lf",&m[i]);
		if (m[i]<0.) return false;
	}	
	
	for (int i=0;i<3;i++) l[i]=l[i]*m[i]*0.5;
	
	int hh,mm,ss;
	scanf("%d:%d:%d",&hh,&mm,&ss);
	st=hh*3600+mm*60+ss;
	scanf("%d:%d:%d",&hh,&mm,&ss);
	ed=hh*3600+mm*60+ss;
	
	if (st>ed) swap(st,ed);
	
	//printf("%d %d\n",st,ed);
	
	double ans=0.;
	for (int i=st;i<ed;i++) {
		double now=((double) i);
	
		double X=(l[0]*cos(a[0]*now)+l[1]*cos(a[1]*now)+l[2]*cos(a[2]*now))/(m[0]+m[1]+m[2]);
		double Y=(l[0]*sin(a[0]*now)+l[1]*sin(a[1]*now)+l[2]*sin(a[2]*now))/(m[0]+m[1]+m[2]);
		
		now=((double)(i+1));
		
		double A=(l[0]*cos(a[0]*now)+l[1]*cos(a[1]*now)+l[2]*cos(a[2]*now))/(m[0]+m[1]+m[2]);
		double B=(l[0]*sin(a[0]*now)+l[1]*sin(a[1]*now)+l[2]*sin(a[2]*now))/(m[0]+m[1]+m[2]);
		
		ans+=sqrt((X-A)*(X-A)+(Y-B)*(Y-B));
	}
	
	printf("%.10f\n",ans);
	
	return true;
}

int main() {
	while (work()) ;

	return 0;
}
