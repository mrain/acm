#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MX=10003;
const double erfen=1e-5;
const double eps=1e-8;
int n;
double x[MX],y[MX],z[MX];
double dis(double a,double b)
{
	return sqrt(a*a+b*b);
}
double calc(double h)
{
	double ret=0;
	for(int i=1;i<=n;++i)
		if(fabs(x[i])>eps||fabs(y[i])>eps)
		{
			double b=dis(x[i],y[i]);
			double a=b*z[i]/(h-z[i]);
			ret=max(ret,a+b);
		}
	return ret;
}
int main()
{
	int _;
	for(scanf("%d",&_);_--;)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%lf%lf%lf",x+i,y+i,z+i);
		double l=0,r=1e10;
		for(int i=1;i<=n;++i)
			l=max(l,z[i]);
		while(r-l>erfen)
		{
			double k1=l+(r-l)/3.;
			double k2=r-(r-l)/3.;
			double a1=calc(k1);
			a1=(a1*a1)*k1;
			double a2=calc(k2);
			a2=(a2*a2)*k2;
			if(a1<a2)r=k2;
			else l=k1;
		}
		printf("%.3f %.3f\n",l,calc(l)); 
	}
	return 0;
}
