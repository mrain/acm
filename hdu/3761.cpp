#include<cstdio>
#include<vector>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<deque>
#include<cmath>
#define A first
#define B second
using namespace std;
int n;
const double eps=1e-8;
inline int sgn(double a)
{
	return a<eps?-1:a>eps?1:0;
}
inline double sqr(double a){
	return a*a;
}
struct point{
	double x,y;
	point(double x=0,double y=0):x(x),y(y){}
	inline void read(){
		scanf("%lf%lf",&x,&y);
	}
	inline point operator +(const point &a)const
	{
		return point(x+a.x,y+a.y);
	}
	inline point operator -(const point &a)const
	{
		return point(x-a.x,y-a.y);
	}
	inline point operator *(const double &a)const
	{
		return point(x*a,y*a);
	}
	inline point operator /(const double &a)const
	{
		return point(x/a,y/a);
	}
};
inline double dot(const point &a,const point &b){
	return a.x*b.x+a.y*b.y;
}
inline double cross(const point &a,const point &b){
	return a.x*b.y-a.y*b.x;
}
inline double ang(const point &a){
	return atan2(a.y,a.x);
}
typedef pair<point,point> hf;

inline point intersect(const hf &a,const hf &b){
	double k=cross(a.A-b.A,b.A-b.B);
	k/=cross(a.A-a.B,b.A-b.B);
	return a.A+(a.B-a.A)*k;
}

inline bool satisfy(const point &a,const hf &b){
	return sgn(cross(a-b.A,b.B-b.A))>0;
}

inline bool cmp(const hf &a,const hf &b)
{
	int ret=sgn(ang(a.B-a.A)-ang(b.B-b.A));
	return ret==0?satisfy(a.A,b):ret<0;
}

inline bool parallel(const hf &a,const hf &b)
{
	return (sgn(cross(a.A-a.B,b.A-b.B))==0);
}

point p[50003];
vector<hf> v;

bool check(int x)
{
	v.clear();
	for(int i=0;i<n;++i)
		v.push_back(hf(p[i],p[(i+x)%n]));
	//stable_sort(v.begin(),v.end(),cmp);
	static deque<hf> q;
	static deque<point> ans;
	q.clear(), ans.clear();
	q.push_back(v[0]);
	for(int i=1;i<(int)v.size();++i){
		//if(sgn(ang(v[i].B-v[i].A)-ang(v[i-1].B-v[i-1].A))==0)continue;
		while(ans.size()&&!satisfy(ans.back(),v[i]))
			ans.pop_back(),q.pop_back();
		while(ans.size()&&!satisfy(ans.front(),v[i]))
			ans.pop_front(),q.pop_front();
		if(parallel(q.back(),v[i]))return false;
		ans.push_back(intersect(q.back(),v[i]));
		q.push_back(v[i]);
	}
	while(ans.size()&&!satisfy(ans.back(),q.front()))
		ans.pop_back(),q.pop_back();
	if(parallel(q.back(),q.front()))return false;
	ans.push_back(intersect(q.back(),q.front()));
	double ret=cross(ans.back(),ans.front());
	for(int i=0;i<(int)ans.size()-1;++i)
		ret+=cross(ans[i],ans[i+1]);
	return fabs(ret)>=eps;
//	return OK;
}
int main()
{
	int _;
	for(scanf("%d",&_);_--;)
	{
		scanf("%d",&n);
		for(int i=0;i<n;++i)
			p[i].read();
		if(n<=4)
		{
			puts("1");
			continue;
		}
//		cout << check(2) << endl;
		int l=1,r=(n+1)/2;
		while(l!=r)
		{
			//cout << l << ' ' << r << endl;
			int mid=(l+r+1)>>1;
			if(check(mid))l=mid;
			else r=mid-1;
		}
		printf("%d\n",l);
	}
	return 0;
}
