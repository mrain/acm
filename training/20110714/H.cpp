#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
const double Pi=acos(-1.);
const double eps=1e-6;
int r,n;
struct rect
{
	int x1,y1,x2,y2;
	rect(){}
	rect(int _x1,int _y1,int _x2,int _y2):x1(_x1),y1(_y1),x2(_x2),y2(_y2){}
}rec[51];
struct point
{
	double x,y;
	point(double _x,double _y):x(_x),y(_y){}
};
bool in(const point &a,const rect &b)
{
	return a.x+eps>b.x1&&a.x-eps<b.x2&&a.y+eps>b.y1&&a.y-eps<b.y2;
}
point GetPoint(double jd)
{
	return point(r*cos(jd),r*sin(jd));
}
double GetJd(point p)
{
	double ret=atan2(p.y,p.x);
	if(ret<0)ret+=2*Pi;
	return ret;
}
double s[1001];
int main()
{
	while(scanf("%d%d",&r,&n)==2)
	{
		int cnt=0;
		for(int i=1;i<=n;++i)
		{
			int x1,y1,x2,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			rec[i]=rect(x1,y1,x2,y2);
			if(abs(x1)<=r)
			{
				double x=x1;
				double y=sqrt(r*r-x*x);
				if(y+eps>y1&&y-eps<y2)
					s[++cnt]=GetJd(point(x,y));
				y=-y;
				if(y+eps>y1&&y-eps<y2)
					s[++cnt]=GetJd(point(x,y));
			}
			if(abs(x2)<=r)
			{
				double x=x2;
				double y=sqrt(r*r-x*x);
				if(y+eps>y1&&y-eps<y2)
					s[++cnt]=GetJd(point(x,y));
				y=-y;
				if(y+eps>y1&&y-eps<y2)
					s[++cnt]=GetJd(point(x,y));
			}
			if(abs(y1)<=r)
			{
				double y=y1;
				double x=sqrt(r*r-y*y);
				if(x+eps>x1&&x-eps<x2)
					s[++cnt]=GetJd(point(x,y));
				x=-x;
				if(x+eps>x1&&x-eps<x2)
					s[++cnt]=GetJd(point(x,y));
			}
			if(abs(y2)<=r)
			{
				double y=y2;
				double x=sqrt(r*r-y*y);
				if(x+eps>x1&&x-eps<x2)
					s[++cnt]=GetJd(point(x,y));
				x=-x;
				if(x+eps>x1&&x-eps<x2)
					s[++cnt]=GetJd(point(x,y));
			}
		}
		bool all=false;
		for(int i=1;i<=n;++i)
			if(in(point(-r,0),rec[i])
			 &&in(point(r,0),rec[i])
			 &&in(point(0,-r),rec[i])
			 &&in(point(0,r),rec[i]))
			 {
			 	all=true;
			 	break;
			 }
		if(all)
		{
			printf("%.3f\n",2*Pi*r);
			continue;
		}
		s[++cnt]=0;
		s[++cnt]=2*Pi;
		sort(s+1,s+cnt+1);
		//for(int i=1;i<=cnt;++i)printf("%.3f\n",s[i]);
		double ans=0;
		for(int i=1;i<cnt;++i)
		{
			double x=s[i];
			double y=s[i+1];
			double z=(x+y)/2.0;
			point p=GetPoint(z);
			bool OK=false;
			for(int j=1;j<=n;++j)
				if(in(p,rec[j]))
				{
					OK=true;
					break;
				}
			if(OK)
				ans+=(y-x)*r;
		}
		printf("%.3f\n",ans);
	}
	return 0;
}

