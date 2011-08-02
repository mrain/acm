#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include<iostream>
using namespace std;

#define maxn (110)
#define PB push_back
#define MP make_pair
#define A first
#define B second
#define eps 1e-6

struct point{
	double x,y;
	
	point(){}
	point(double a,double b):x(a),y(b){}
	
	point operator+(const point& a) const {
		return point(x+a.x,y+a.y);
	}
	
	point operator-(const point& a) const {
		return point(x-a.x,y-a.y);
	}
	
	point operator*(double a) {
		point point(x*a,y*a);
	}
	
	point operator/(double a) {
		return point(x/a,y/a);
	}
	
	double mod() {
		return sqrt(x*x+y*y);
	}
};

struct seg{
	point a,b;
	
	seg(){}
	seg(const point& A,const point& B):a(A),b(B){}
};

vector<point> g[maxn];
double D[maxn][maxn];
int f[maxn];
int n;
double w;

const point ST=point(0.,0.);

int find(int x) {
	return f[x] == x ? x : f[x] = find(f[x]);
}

void gat(int x,int y) {
	x=find(x),y=find(y);
	
	if (x!=y) f[x]=y;
}

inline double dot(const point& a,const point& b) {
	return a.x*b.x+a.y*b.y;
}

inline double cross(point a,point b) {
	return a.x*b.y-a.y*b.x;
}

double dist(const point& u,seg v) {
	point a=u-v.a,b=v.b-v.a,c=v.b-u;

	double delta=dot(a,b)/b.mod();
	
	if (delta<eps||delta>b.mod()) return min(a.mod(),c.mod());
	
	//delta/=b.mod();
	return sqrt(a.mod()*a.mod()-delta*delta);
}

bool inside(const point& u,vector<point>& v) {
	double alpha=0.;
	
	point a,b;
	for (int i=0;i<v.size()-1;i++) {
		a=v[i]-u,b=v[i+1]-u;
	
		alpha+=asin(cross(a,b)/a.mod()/b.mod());
	}
	
	return fabs(alpha)>2.*acos(-1.)-eps;
}

bool ok(seg u,seg v) {
	if (cross(v.a-u.a,u.b-u.a)*cross(v.b-u.a,u.b-u.a) > eps) return false;
	
	swap(u,v);
	if (cross(v.a-u.a,u.b-u.a)*cross(v.b-u.a,u.b-u.a) > eps) return false;
	
	return true;
}

bool intersect(vector<point>& a,vector<point>& b) {
	for (int i=0;i<a.size()-1;i++)
		for (int j=0;j<b.size()-1;j++)	
			if (ok(seg(a[i],a[i+1]),seg(b[j],b[j+1]))) return true;

	return false;
}

bool check(double x) {
	for (int i=1;i<=n;i++) 
		if (D[0][i]<x) return false;
	
	for (int i=0;i<=n+1;i++) f[i]=i;
	
	for (int i=1;i<=n;i++) {
		bool flag=false;
		
		for (int j=0;j<g[i].size()-1&&!flag;j++) 
			if (g[i][j].y+w<x) flag=true;
			
		if (flag) gat(0,i);
	}
	
	for (int i=1;i<=n;i++) {
		bool flag=false;
		
		for (int j=0;j<g[i].size()-1&&!flag;j++) 
			if (w-g[i][j].y<x) flag=true;
			
		if (flag) gat(n+1,i);
	}
	
	for (int i=1;i<=n;i++) 
		for (int j=i+1;j<=n;j++) 
			if (D[i][j]<x) gat(i,j);
	
	if (find(0)==find(n+1)) return false;
	
	return true;
}

void calc_D() {
	memset(D,0,sizeof(D));
	
	for (int i=1;i<=n;i++) {
		D[0][i] = 1e100;
		if (inside(ST, g[i])) D[0][i] = 0;
		else
			for (int j=0;j<g[i].size()-1;j++)
				D[0][i]=min(D[0][i],dist(ST,seg(g[i][j],g[i][j+1])));
	}
	
	for (int a=1;a<=n;a++)
		for (int b=1;b<=n;b++) {
			D[a][b]=1e100;
			
			if (intersect(g[a],g[b])) {
				D[a][b]=0.; continue;
			}
			
			for (int i=0;i<g[a].size();i++) {
				if (inside(g[a][i],g[b])) {
					D[a][b]=0.; break;
				}
				
				for (int j=0;j<g[b].size()-1;j++)
					D[a][b]=min(D[a][b],dist(g[a][i],seg(g[b][j],g[b][j+1])));
			}
		}
		
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			D[i][j]=min(D[i][j],D[j][i]);
	/*for (int i=0;i<=n;i++) {
		printf("%d: ===================\n",i);
		
		for (int j=i+1;j<=n;j++) printf("%.2f ",D[i][j]);
		
		puts("");
	}*/
}

int main(){

	while (scanf("%lf%d",&w,&n)==2) {
		if (w<eps&&n==0) break; 
		
		for (int i=1;i<=n;i++) g[i].clear();
		
		for (int i=1;i<=n;i++) {
			int sum; scanf("%d",&sum);
			
			for (int j=0;j<sum;j++) {
				double x,y; scanf("%lf%lf",&x,&y);
				
				g[i].PB(point(x,y));
			}
			
			g[i].PB(g[i][0]);
		}
		
		w/=2.; calc_D();
//		cout << check(1.) << endl;
	//	break;
		double l=0.,r=2*w,ans=-1.;
		while (l+eps<r) {
			double mid=(l+r)/2.;
			
			if (check(mid)) ans=l=mid;
			else r=mid;
		}
		
		if (ans<0) puts("impossible");
		else printf("%.2f\n",ans*0.5);
	}

	return 0;
}


