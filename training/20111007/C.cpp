#include<cmath>
#include <iostream>
#include<cstdio>
#include<vector>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const double eps=1e-8;
const double oo=1e20;
inline double mysqrt(double x) {
	return sqrt(max(x, eps));
}
inline int sig(double x){
	return (x>eps)-(x<-eps);
}
inline double sqr(double x){
	return x*x;
}
struct point{
	double x,y;
	point(){}
	point(double x,double y):x(x),y(y){}
	inline point resize(double d){
		d/=mysqrt(x*x+y*y);
		return point(x*d,y*d);
	}
	inline point left90(){
		return point(-y,x);
	}
	inline point operator -(const point &o)const{
		return point(x-o.x,y-o.y);
	}
	inline point operator +(const point &o)const{
		return point(x+o.x,y+o.y);
	}
	inline point operator *(double d)const{
		return point(x*d,y*d);
	}
};
struct circle{
	point center;
	double radis;
};
inline double cross(point o,point a,point b){
	return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
inline double dot(point o,point a,point b){
	return (a.x-o.x)*(b.x-o.x)+(a.y-o.y)*(b.y-o.y);
}
inline double dis(point a,point b){
	return mysqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}
inline double radian(point o,point a,point b){
	return acos(dot(o,a,b)/(dis(o,a)*dis(o,b)));
}
inline double pointToLine(point o,point a,point b,point &res){
	double d=dis(a,b);
	double s=cross(a,b,o)/d;
	res=o+(a-b).left90()*(s/d);
	return fabs(s);
}
inline int intersect(point a,point b,circle c,point &p1,point &p2){
	point p;
	double d=pointToLine(c.center,a,b,p);
	int v=sig(c.radis-d);
	if(v!=-1){
		point vec=(b-a).resize(mysqrt(sqr(c.radis)-sqr(d)));
		p1=p+vec;
		p2=p-vec;
	}
	return v;
}
int intersect(circle a,circle b,point &p1,point &p2){
	double d=dis(a.center,b.center);
	int s1=sig(d-fabs(a.radis-b.radis));
	int s2=sig(d-fabs(a.radis+b.radis));
	if(sig(d)==0&&s1<0)return sig(a.radis-b.radis);
	if(s2>0)return 2;
	double t=(sqr(a.radis)+sqr(d)-sqr(b.radis))/(2*d);
	point p=(b.center-a.center).resize(t)+a.center;
	point vec=(b.center-a.center).left90().resize(mysqrt(sqr(a.radis)-sqr(t)));
	p1=p+vec;
	p2=p-vec;
	if(s1==0)return 3*sig(a.radis-b.radis);
	if(s2==0)return 4;
	return 5;
}
int n;
circle c[31];
vector<point> a;
vector< pair<double,double> > h;
bool check(point a,point b){
	double ym=dot(a,b,b);
	h.clear();
	for(int i=1;i<=n;++i) {
		point p1,p2;
		int tmp=intersect(a,b,c[i],p1,p2);
		if(tmp==1){
			double x=dot(a,b,p1);
			double y=dot(a,b,p2);
			if(x>y)swap(x,y);
			if(x<0)x=0;
			if(y>ym)y=ym;
			h.push_back(make_pair(x-eps,y+eps));
		}
	}
	stable_sort(h.begin(),h.end());
	double y=0;
	for(int i=0;i<h.size();++i)
		if(sig(h[i].first-y)>0)
			break;
		else
			y=max(y,h[i].second);
	return sig(y-ym)>=0;
}

vector< pair<int,double> > e[2003];
inline void addEdge(int x,int y,double v){
	e[x].push_back(make_pair(y,v));
}
double d[2003];
bool vis[2003];
int main(){
	int _,cas=0;
	for(scanf("%d",&_);_--;){
		scanf("%d",&n);
		a.clear();
		int S=0,T=1;
		for(int i=1;i<=n;++i){
			int x,y,r;
			scanf("%d%d%d",&x,&y,&r);
			c[i].center=point(x,y);
			if (i == 1 || i == n) a.push_back(point(x,y));
			c[i].radis=r;
		}
		for(int i=1;i<=n;++i)
			for(int j=i + 1;j<=n;++j) {
				point p1,p2;
				int tmp=intersect(c[i],c[j],p1,p2);
				//printf("%d %d %d\n", i, j, tmp);
				if(tmp==0||tmp==1||tmp==-1||tmp==2)continue;
				if(tmp==3||tmp==-3||tmp==4||tmp==5) a.push_back(p1);
				if(tmp==5) a.push_back(p2);
			}
//		return 0;
		for(int i=0;i<a.size();++i) {
			e[i].clear();
			//printf("%.4f %.4f\n", a[i].x, a[i].y);
		}
		for(int i=0;i<a.size();++i)
			for(int j=i+1;j<a.size();++j)
				if(check(a[i],a[j])){
printf("(%.4f, %.4f) -> (%.4f, %.4f), %.4f\n", a[i].x, a[i].y, a[j].x, a[j].y, dis(a[i], a[j]));
					addEdge(i,j,dis(a[i],a[j]));
					addEdge(j,i,dis(a[i],a[j]));
				}
		n=a.size();
		for(int i=0;i<n;++i)
			d[i]=oo;
		d[0]=0;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;++i){
			double mv=1e10;
			int s1=-1;
			for(int j=0;j<n;++j)
				if(!vis[j]&&d[j]<mv)
					mv=d[j],s1=j;
			if(s1==-1 || s1 == T)break;
			vis[s1]=1;
			for(int j=0;j<e[s1].size();++j){
				int s2=e[s1][j].first;
				if(vis[s2])continue;
				if(d[s1]+e[s1][j].second<d[s2])
					d[s2]=d[s1]+e[s1][j].second;
			}
		}
		printf("Case %d: ",++cas);
		if(d[T]>=1e15)puts("No such path.");
		else printf("%.4f\n",d[T]);
	}
	return 0;
}
