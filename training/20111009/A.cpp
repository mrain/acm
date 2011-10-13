#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;
const double eps=1e-8;
typedef long long ll;
int sig(const double d){
	//return (d>eps)-(d<-eps);
	return d < -eps ? -1 : d > eps ? 1 : 0;
}
inline ll gcd(ll x,ll y){
	while(y){
		ll tmp=x%y;
		x=y;
		y=tmp;
	}
	return x;
}
inline ll sqr(ll x){
	return x*x;
}
inline double sqr(double x){
	return x*x;
}
struct fac{
	ll x,y;
	fac(){}
	fac(ll x):x(x),y(1){}
	fac(ll _x,ll _y){
		ll g=gcd(_x,_y);
		x=_x/g;
		y=_y/g;
	}
	fac operator +(const fac &a)const {
		fac ret;
		ret.y=y*a.y/gcd(y,a.y);
		ret.x=x*(ret.y/y)+a.x*(ret.y/a.y);
		ll g=gcd(ret.x,ret.y);
		ret.x/=g,ret.y/=g;
		return ret;
	}
	fac operator -(const fac &a) const {
		fac ret;
		ret.y=y*a.y/gcd(y,a.y);
		ret.x=x*(ret.y/y)-a.x*(ret.y/a.y);
		ll g=abs(gcd(ret.x,ret.y));
		ret.x/=g,ret.y/=g;
		return ret;
	}
	fac operator *(const fac &a) const {
		fac ret(x*a.x,y*a.y);
		ll g=abs(gcd(ret.x,ret.y));
		ret.x/=g,ret.y/=g;
		return ret;
	}
};
bool operator <(const fac &a,const fac &b){
	fac ret=a-b;
	return ret.x<0;
}

struct ipoint{
	ll x,y,z;
	ipoint(){}
	ipoint(ll x,ll y,ll z):x(x),y(y),z(z){}
	ipoint operator + (const ipoint &p)const{
		return ipoint(x+p.x,y+p.y,z+p.z);
	}
	ipoint operator - (const ipoint &p)const{
		return ipoint(x-p.x,y-p.y,z-p.z);
	}
	ipoint operator *(ll d)const{
		return ipoint(x*d,y*d,z*d);
	}
	ll len()const{
		return x*x+y*y+z*z;
	}
	void read(){
		int xx,yy,zz;
		scanf("%d%d%d",&xx,&yy,&zz);
//		cin >> xx >> yy >> zz;
		x=xx,y=yy,z=zz;
	}
};
ipoint cross(const ipoint &a,const ipoint &b){
	return ipoint(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}
ipoint cross(const ipoint &o,const ipoint &a,const ipoint &b){
	return cross(a-o,b-o);
}
ll dot(const ipoint &a,const ipoint &b){
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

ll dis(const ipoint &a,const ipoint &b){
	return (a-b).len();
}

fac dis(const ipoint &a,const ipoint &b,const ipoint &c,const ipoint &d){
	ipoint fa=cross(b-a,d-c);
	if(fa.len()==0)
		return fac(cross(c,a,b).len(),dis(a,b));
	else return fac(sqr(dot(c-a,fa)),fa.len());
}
fac idis(const ipoint &a,const ipoint &b,const ipoint &c){
	return fac(cross(a,b,c).len(),dis(b,c));
}
fac dis(const ipoint &a,const ipoint &b,const ipoint &c){
	ll d=dot(a-b,c-b);
	ll ym=dot(c-b,c-b);
	if(d<0||d>ym)return min(dis(a,b),dis(a,c));
	else return idis(a,b,c);
}

struct point{
	double x,y,z;
	point(){}
	point(double x,double y,double z):x(x),y(y),z(z){}
	point(ipoint a){
		x=a.x,y=a.y,z=a.z;
	}
	point operator + (const point &p)const{
		return point(x+p.x,y+p.y,z+p.z);
	}
	point operator - (const point &p)const{
		return point(x-p.x,y-p.y,z-p.z);
	}
	point operator *(double d)const{
		return point(x*d,y*d,z*d);
	}
	point operator /(double d)const{
		return point(x/d,y/d,z/d);
	}
	double len()const{
		return x*x+y*y+z*z;
	}
	void read(){
		int xx,yy,zz;
		scanf("%d%d%d",&xx,&yy,&zz);
		x=xx,y=yy,z=zz;
	}
};

point cross(const point &a,const point &b){
	return point(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}
point cross(const point &o,const point &a,const point &b){
	return cross(a-o,b-o);
}
double dot(const point &a,const point &b){
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

double dis(const point &a,const point &b){
	return (a-b).len();
}

double dis(const point &a,const point &b,const point &c,const point &d){
	point fa=cross(b-a,d-c);
	if(fa.len()==0)
		return cross(c,a,b).len()/dis(a,b);
	else return sqr(dot(c-a,fa))/fa.len();
}
double ldis(const point &a,const point &b,const point &c){
	return cross(a,b,c).len()/dis(b,c);
}
double dis(const point &a,const point &b,const point &c){
	double d=dot(a-b,c-b);
	double ym=dot(c-b,c-b);
	if(d<eps||d>ym-eps)return min(dis(a,b),dis(a,c));
	else return ldis(a,b,c);
}

int main(){
	int _;
	for(scanf("%d",&_);_--;){
		ipoint a,b,c,d;
		a.read();
		b.read();
		c.read();
		d.read();
		point r1=a,r2=b,r3=c,r4=d;
		double di=dis(r1,r2,r3,r4);
		point l=r1,r=r2;
		for(int cas=0;cas<100;++cas){
			point m1=l+(r-l)/3.;
			point m2=r-(r-l)/3.;
			if(dis(m1,r3,r4)<dis(m2,r3,r4))r=m2;
			else l=m1;
		}
		//printf("%.4f\n",dis(l,r3,r4));
		//cout << dis(b,c,d).x << ' ' << dis(b,c,d).y << endl;
		fac ans(0);
		if(sig(dis(l,r3,r4)-di)==0)ans=dis(a,b,c,d);
		else ans=min(min(dis(a,c,d),dis(b,c,d)), min(dis(c,a,b), dis(d,a,b)));
//		printf("%d %d\n",ans.x,ans.y);
		cout << ans.x << ' ' << ans.y << endl;
	}
	return 0;
}
