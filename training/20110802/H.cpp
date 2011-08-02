#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const double eps=1e-8;
double rt;
struct point
{
	double x,y;
	point(){}
	point(double x,double y):x(x),y(y){}
	double MOD(){
		return sqrt(x*x+y*y);
	}
	point operator +(const point &a)const{
		return point(x+a.x,y+a.y);
	}
	point operator -(const point &a)const{
		return point(x-a.x,y-a.y);
	}
	point operator *(const double &a)const{
		return point(x*a,y*a);
	}
	point operator /(const double &a)const{
		return point(x/a,y/a);
	}
	point resize(double x){
		double tmp=x/(*this).MOD();
		return (*this)*tmp;
	}
	point left90(){
		return point(-y,x);
	}
}t;
inline double sqr(double x){
	return x*x;
}
inline double sgn(double x){
	return x<-eps?-1:x>eps?1:0;
}
inline double cross(point a,point b){
	return a.x*b.y-a.y*b.x;
}
inline double cross(point x,point y,point z){
	return cross(y-x,z-x);
}
void put(point a,point b){
	t=(a+b)/2.0;
	rt=(a-t).MOD();
}
void put(point a,point b,point c)
{
	if(sgn(cross(a,b,c))==0)
	{
		double dis=max((a-b).MOD(),(a-c).MOD());
		dis=max(dis,(b-c).MOD());
		if(sgn(dis-(a-b).MOD())==0)put(a,b);
		else if(sgn(dis-(a-c).MOD())==0)put(a,c);
		else put(b,c);
		return;
	}
	double s=fabs(cross(a,b,c))*2;
	if(sgn(cross(a,b,c))<0)swap(a,b);
	rt=(a-b).MOD()*(a-c).MOD()*(b-c).MOD()/s;
	point fa=(b-a).left90();
	fa=fa.resize(sqrt(sqr(rt)-sqr((b-a).MOD()/2.0)));
	t=(a+b)/2.0+fa;
}
bool inside(point x)
{
	return (x-t).MOD()<rt+eps;
}
int n,c;
point a[17];
double small[65537],f[65537][17];
int main()
{
	int _;
	for(scanf("%d",&_);_--;)
	{
		scanf("%d%d",&n,&c);
		for(int i=1;i<=n;++i)
			scanf("%lf%lf",&a[i].x,&a[i].y);
		for(int i=0;i<(1<<n);++i)
			small[i]=1e100;
		for(int i=1;i<=n;++i)
		{
			int v=(1<<(i-1));
			small[v]=0;
		}
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
			{
				put(a[i],a[j]);
				int s=0;
				for(int k=1;k<=n;++k)
					if(inside(a[k]))
						s|=1<<(k-1);
				small[s]=min(small[s],rt);
			}
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				for(int k=1;k<=n;++k)
				{
					put(a[i],a[j],a[k]);
					int s=0;
					for(int l=1;l<=n;++l)
						if(inside(a[l]))
							s|=1<<(l-1);
					small[s]=min(small[s],rt);
				}
		for(int i=0;i<(1<<n);++i)
			for(int j=i;j;j=(j-1)&i)
				small[j]=min(small[j],small[i]);
		for(int i=0;i<=c;++i)
			f[0][i]=0;
		for(int i=1;i<(1<<n);++i)
		{
			f[i][0]=1e100;
			for(int j=1;j<=c;++j)
			{
				f[i][j]=f[i][j-1];
				for(int k=i;k;k=(k-1)&i)
					f[i][j]=min(f[i][j],max(small[k],f[i^k][j-1]));
			}
		}
		double ans=1e100;
		for(int i=1;i<=c;++i)
			ans=min(ans,f[(1<<n)-1][i]);
		printf("%.6f\n",ans);
	}
	return 0;
}
