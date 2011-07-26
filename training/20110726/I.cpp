#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const double eps=1e-8;
const double erfen=1e-9;
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
	point left90()const{
		return point(-y,x);
	}
	double mod()const{
		return sqrt(x*x+y*y);
	}
}p[503],ge[503],pp[503];
double cross(const point &a,const point &b)
{
	return a.x*b.y-a.y*b.x;
}
#define zero(x) (((x)>0?(x):-(x))<eps)
double xmult(point p1,point p2,point p0)
{
	return cross(p1-p0,p2-p0);
}
int same_side(point p1,point p2,point l1,point l2)
{
	return xmult(l1,p1,l2)*xmult(l1,p2,l2)>eps;
}
point intersection(point u1,point u2,point v1,point v2){
	point ret=u1;
	double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))
			 /((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
	ret=ret+(u2-u1)*t;
	return ret;
}
void polygon_cut(int &n,point *p,point l1,point l2,point side)
{
	int m=0,i;
	for(i=0;i<n;++i){
		if(same_side(p[i],side,l1,l2))
			pp[m++]=p[i];
			if(!same_side(p[i],p[i+1],l1,l2)&&!(zero(xmult(p[i],l1,l2))&&zero(xmult(p[i+1],l1,l2))))
				pp[m++]=intersection(p[i],p[i+1],l1,l2);
	}
	for(n=i=0;i<m;++i)
		if(!i||!zero(pp[i].x-pp[i-1].x)||!zero(pp[i].y-pp[i-1].y))
			p[n++]=pp[i];
	if(n>1&&zero(p[n-1].x-p[0].x)&&zero(p[n-1].y-p[0].y))
		--n;
	if (n < 3) n = 0;
	p[n]=p[0];
}
bool check(double v,int n)
{
	memcpy(ge,p,sizeof(p));
	int nn=n;
	for(int i=0;i<n;++i)
	{
		point x=p[i];
		point y=p[i+1];
		point fa=(y-x).left90();
		fa=fa*(v/fa.mod());
		//cout << fa.x << ' ' << fa.y << endl;
		polygon_cut(nn,ge,x+fa,y+fa,x+fa+fa);
//		cout << nn << endl;
//		for (int k = 0; k < nn; ++ k)
//			cout << ge[k].x << ' ' << ge[k].y << endl;
		if(!nn)return false;
	}
	return true;
}
int main()
{
	int n;
	while(scanf("%d",&n),n)
	{
		for(int i=0;i<n;++i)
		{
			double x,y;
			scanf("%lf%lf",&x,&y);
			p[i]=point(x,y);
		}
		p[n]=p[0];
//		check(5001.,n);
//		break;
		double l=0,r=1e10;
		while(r-l>erfen)
		{
			double mid=(l+r)/2.0;
			if(check(mid,n))l=mid;
			else r=mid;
		}
		printf("%.7f\n",l);
	}
	return 0;
}
