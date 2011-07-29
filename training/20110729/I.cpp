#include<cstdio>
#include<complex>
using namespace std;
typedef complex<double> point;
point a[103],b[103];
const double eps=1e-8;
inline double sqr(double x){
	return x*x;
}
double calc(point a,point b){
	return sqrt(double(sqr(a.real()-b.real())+sqr(a.imag()-b.imag())));
}
inline double mod(point a){
	return sqrt(double(sqr(a.real())+sqr(a.imag())));
}
inline double dot(point a,point b){
	return a.real()*b.real()+a.imag()*b.imag();
}
double calc(point a,point b,point c){
	double ret=min(calc(a,b),calc(a,c));
	double v=dot(b-c,a-c)/mod(b-c);
	if(v>eps&&v<=mod(b-c))return sqrt(mod(a-c)*mod(a-c)-v*v);
	else return ret;
}
int main()
{
	int _;
	for(scanf("%d",&_);_--;)
	{
		int n1,n2;
		scanf("%d",&n1);
		for(int i=1;i<=n1;++i)
		{
			double x,y;
			scanf("%lf%lf",&x,&y);
			a[i]=point(x,y);
		}
		scanf("%d",&n2);
		for(int i=1;i<=n2;++i)
		{
			double x,y;
			scanf("%lf%lf",&x,&y);
			b[i]=point(x,y);
		}
		a[n1+1]=a[1];
		b[n2+1]=b[1];
		double dis=1e100;
		for(int i=1;i<=n1;++i)
			for(int j=1;j<=n2;++j)
				dis=min(dis,calc(a[i],b[j],b[j+1]));
		for(int j=1;j<=n2;++j)
			for(int i=1;i<=n1;++i)
				dis=min(dis,calc(b[j],a[i],a[i+1]));
		printf("%.8f\n",dis * 0.5);
	}
	return 0;
}
