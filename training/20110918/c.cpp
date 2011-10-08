#include<cmath>
#include <vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 503
#define sqr(v) ((v)*(v))
const double eps=1e-8;
const double pi = acos(-1.);

inline int sgn(double d){
	return (d>eps)-(d<-eps);
}

struct point2{
	double x, y;
	point2(double x = 0, double y = 0)
		:x(x), y(y) {}
	point2 operator +(const point2 &p)const{
		return point2(x+p.x,y+p.y);
	}
	point2 operator -(const point2 &p)const{ return point2(x-p.x,y-p.y);
	}
	point2 operator *(const double &d)const{
		return point2(x*d,y*d);
	}
};

inline double cross(const point2 &a, const point2 &b) {
	return a.x * b.y - a.y * b.x;
}

inline double dot(const point2 &a, const point2 &b) {
	return a.x * b.x + a.y * b.y;
}

inline double norm(const point2 &a) { return dot(a, a); }
inline double len(const point2 &a) { return sqrt(norm(a)); }

struct point{
	double x,y,z;
	point(double x,double y,double z):x(x),y(y),z(z){}
	point(){}
	point operator +(const point &p)const{
		return point(x+p.x,y+p.y,z+p.z);
	}
	point operator -(const point &p)const{
		return point(x-p.x,y-p.y,z-p.z);
	}
	point operator *(const double &d)const{
		return point(x*d,y*d,z*d);
	}
	point resize(double d){
		d/=sqrt(x*x+y*y+z*z);
		return point(x*d,y*d,z*d);
	}
	bool operator <(const point &p)const{
		return sgn(x-p.x)!=0?x<p.x:sgn(y-p.y)!=0?y<p.y:sgn(z-p.z)<0;
	}
	bool operator ==(const point &p)const{
		return !sgn(x-p.x)&&!sgn(y-p.y)&&!sgn(z-p.z);
	}
};
double dot(const point &a,const point &b){
	return a.x*b.x+a.y*b.y+a.z*b.z;
}
double norm(const point &a) { return dot(a, a); }
double len(const point &a) { return sqrt(norm(a)); }
double dot(const point &o,const point &a,const point &b){
	return dot(a-o,b-o);
}
point cross(const point &a,const point &b){
	return point(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}
point cross(const point &o,const point &a,const point &b){
	return cross(a-o,b-o);
}

inline bool sameface(const point &a, const point &b, const point &c, const point &d) {
	return sgn(dot(b - a, cross(a, c, d))) == 0;
}

bool isintersect(const point2 &u1, const point2 &u2, const point2 &v1, const point2 &v2) {
	if (sgn(cross(v1 - u1, u2 - u1)) * sgn(cross(v2 - u1, u2 - u1)) != -1) return false;
	if (sgn(cross(u1 - v1, v2 - v1)) * sgn(cross(u2 - v1, v2 - v1)) != -1) return false;
	return true;
}

inline point2 intersect(const point2 &u1, const point2 &u2, const point2 &v1, const point2 &v2) {
	if (sgn(cross(u1 - u2, v1 - v2)) == 0) return point2(-1, -1);
	double t = cross(u1 - v1, v1 - v2) / cross(u1 - u2, v1 - v2);
	return u1 + (u2 - u1) * t;
}

struct face {
	point a, b, c;
	face() {}
	face(point a, point b, point c) : a(a), b(b), c(c) {}
	point fa() const {
		return cross(a, b, c);
	}
	bool same_side(const point &p, const point &q) const {
		return sgn( dot(a - q, cross(q, b, c)) * dot(a - p, cross(p, b, c))) > 0;
	}
	bool inface(const point &q) const {
		return sameface(a, b, c, q);
	}

	bool operator ==(const face& f) const {
		point fa1 = fa();
		point fa2 = f.fa();
		if (sgn(len(cross(fa1, fa2))) != 0) return false;
		return inface(f.a);
	}
};

bool px(const face &f, const point &a, const point &b) {
	return sgn(dot(f.fa(), b - a)) == 0;
}

point intersect(const face &f, const point &a, const point &b) {
	point fa = f.fa();
	double t = dot(fa, f.a - a) / dot(fa, b - a);
	return a + (b - a) * t;
}

void intersect(const face &f1, const face &f2, point &p1, point &p2) {
	p1 = (false == px(f2, f1.a, f1.b)) ? intersect(f2, f1.a, f1.b) : intersect(f2, f1.b, f1.c);
	p2 = p1 + cross(f1.fa(), f2.fa());
}

bool insegment(const point2 &a, const point2 &u1, const point2 &u2) {
	if (sgn(cross(a - u2, u1 - u2)) != 0) return false;
	double l = len(u2 - u1);
	double x = dot(a - u1, u2 - u1) / l;
	if (x < -eps || x > l + eps) return false;
	return true;
}

struct polygon {
	vector<point> p;
	vector<point2> p2;
	face f;
	point base_x, base_y, base;

	void clear() {
		p.clear();
		p2.clear();
	}

	point2 f3to2(const point &a) const {
		point tmp = a - base;
		return point2(dot(base_x, tmp), dot(base_y, tmp));
	}

	point f2to3(const point2 &a) const {
		return base + base_x * a.x + base_y * a.y;
	}

	void init() {
		f.a = p[0]; f.b = p[1]; f.c = p[2];

		base = p[0];
		base_x = p[1] - p[0];
		point base_z = cross(p[2] - p[1], base_x);
		base_y = cross(base_x, base_z);
		base_x = base_x * (1. / len(base_x));
		base_y = base_y * (1. / len(base_y));

		for (int i = 0; i < (int)p.size(); ++ i)
			p2.push_back(f3to2(p[i]));
	}

	bool inpolygon(const point &a) const{
		point2 u1 = f3to2(a);
		point2 u2 = point2(301542, 3212288);

		int m = (int)p2.size(), cnt = 0;

//		printf("%.3f %.3f %.3f\n", a.x, a.y, a.z);

		for (int i = 0; i < m; ++ i) {
			point2 v1 = p2[i], v2 = p2[(i + 1) % m];
			if (insegment(u1, v1, v2)) {
//				printf("%.3f %.3f %.3f %.3f %.3f %.3f\n", u1.x, u1.y, v1.x, v1.y, v2.x, v2.y);
				return true;
			}
			if (isintersect(u1, u2, v1, v2)) ++ cnt;
		}
		return (cnt & 1) == 1;
	}

	void intersect(const point &a, const point &b, vector <point> &ret) {
		point2 u1 = f3to2(a), u2 = f3to2(b);

		int m = (int)p2.size();
		for (int i = 0; i < m; ++ i) {
			point2 v1 = p2[i], v2 = p2[(i + 1) % m];
			if (sgn(cross(u1 - u2, v1 - v2)) == 0) continue;
			point2 x = ::intersect(u1, u2, v1, v2);

			if (insegment(x, v1, v2)) ret.push_back(f2to3(x));
		}
	}

}a, b;

int n, m;

int main(){
	while (scanf("%d%d", &m, &n) == 2 && (n || m)) {
		a.clear(); b.clear();

		for (int i = 0; i < m; ++ i) {
			point t;
			scanf("%lf%lf%lf", &t.x, &t.y, &t.z);
			a.p.push_back(t);
		}

		for (int i = 0; i < n; ++ i) {
			point t;
			scanf("%lf%lf%lf", &t.x, &t.y, &t.z);
			b.p.push_back(t);
		}

		a.init(); b.init();

		if (sgn(len(cross(a.f.fa(), b.f.fa()))) == 0) {
			if (!(a.f == b.f)) puts("NO");
			else {
				bool flag = false;
				for (int i = 0; i < (int)a.p.size(); ++ i)
					if (b.inpolygon(a.p[i]))
						flag = true;
				for (int i = 0; i < (int)b.p.size(); ++ i)
					if (a.inpolygon(b.p[i]))
						flag = true;

				for (int i = 0; i < (int)a.p2.size() && !flag; ++ i) {
					point2 u1 = a.p2[i], u2 = a.p2[(i + 1) % (int)a.p2.size()];
					for (int j = 0; j < (int)b.p2.size() && !flag; ++ j) {
						point2 v1 = b.p2[i], v2 = b.p2[(i + 1) % (int)b.p2.size()];
						if (isintersect(u1, u2, v1, v2)) flag = true;
					}
				}
				puts(flag ? "YES" : "NO");
			}
			continue;
		}

		point u1, u2;
		intersect(a.f, b.f, u1, u2);
		//extend u1, u2
		u2 = u1 + (u2 - u1) * 10000.;
		u1 = u2 + (u1 - u2) * 10000.;

		vector <point> event;
		a.intersect(u1, u2, event);
		b.intersect(u1, u2, event);
		
		bool flag = false;
		for (int i = 0; i < (int)event.size(); ++ i) {
//			printf("%.3f %.3f %.3f\n", event[i].x, event[i].y, event[i].z);
			if (a.inpolygon(event[i]) && b.inpolygon(event[i])) {
				flag = true;
				break;
			}
		}
		puts(flag ? "YES" : "NO");

	}
	return 0;
}

