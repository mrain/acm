#include<cstdio>
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;
const double eps=1e-6;
const double erfen=1e-8;
struct point
{
	double x,y;
	point(){}
	point(double _x,double _y):x(_x),y(_y){}
	point operator -(const point &a)const{
		return point(x-a.x,y-a.y);
	}
	point operator +(const point &a)const{
		return point(x+a.x,y+a.y);
	}
	point operator *(const double a)const{
		return point(x*a,y*a);
	}
	double mod()const{
		return sqrt(x*x+y*y);
	}
}p[503],ge[503];
	int n;
double dot(const point &a,const point &b)
{
	return a.x*b.x+a.y*b.y;
}
double point2line(const point &x,const point &a,const point &b)
{
//	cout << (x-a).x << ' ' << (x-a).y << ' ' << (b-a).x << ' ' << (b-a).y << endl;
	double s=dot(x-a,b-a)/(b-a).mod();
//	cout << s << endl;
	if(s<eps)return (x-a).mod();
	else if(s+eps>(b-a).mod())return (x-b).mod();
	else return sqrt((x-a).mod()*(x-a).mod()-s*s);
}
double calc(point a)
{
	double ret=1e100;
	for(int i=1;i<=n;++i) {
		//cout << a.x << ' ' << a.y << ' ' << p[i].x << ' ' << p[i].y << ' ' << p[i + 1].x << ' ' << p[i + 1].y << ' ' <<point2line(a,p[i],p[i+1]) << endl;
		ret=min(ret,point2line(a,p[i],p[i+1]));
	}
	//printf("%.3f %.3f %.3f\n",a.x,a.y,ret);
	return ret;
}
double calc(double x)
{
	double ly=1e100,ry=1e-100;
	for(int i=1;i<=n;++i)
	{
		double x1=min(p[i].x,p[i+1].x);
		double x2=max(p[i].x,p[i+1].x);
		if(x+eps>x1&&x<x2+eps)
			if(fabs(x1-x2)<eps)
			{
				ly=min(ly,min(p[i].y,p[i+1].y));
				ry=max(ry,max(p[i].y,p[i+1].y));
			}
			else
			{
				double tmp=((x-p[i].x)/(p[i + 1].x-p[i].x));
				double y = p[i].y + (p[i + 1].y - p[i].y) * tmp;
				ly=min(ly,y);
				ry=max(ry,y);
			}
	}
	//cout << x << ' ' << ly << ' ' << ry << endl;
	double ans = -1.;
	while(ry-ly>erfen)
	//for (int step=0; step<50; ++ step)
	{
		double k1 = ly + (ry - ly) / 3.;
		double k2 = ry - (ry - ly) / 3.;
		double a1 = calc(point(x,k1)), a2 = calc(point(x, k2));
		ans=max(ans,max(a1,a2));
		if(a1>a2)ry=k2;
		else ly=k1;
	}
	ans=max(ans,max(calc(point(x,ly)), calc(point(x,ry))));
	return ans;
}
int main()
{
	while(scanf("%d",&n),n)
	{
		double l = 1e100, r = 1e-100;
		for(int i=0;i<n;++i)
		{
			double x,y;
			scanf("%lf%lf",&x,&y);
			p[i]=point(x,y);
			l=min(l,x);
			r=max(r,x);
		}
		p[n]=p[0];
		double ans = -1.;
		while(r-l>erfen)
		{
			//ouble mid=(l+r)/2.0;
			double k1 = l + (r - l) / 3.;
			double k2 = r - (r - l) / 3.;
			double a1 = calc(k1), a2 = calc(k2);
			ans = max(ans, max(a1, a2));
			if (a1 > a2) r = k2;
			else l = k1;
		}
		printf("%.7f\n",ans);
	}
	return 0;
}
