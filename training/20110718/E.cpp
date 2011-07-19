#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

#define maxn (300)

int n;
double ans;
double x[maxn],y[maxn],v[maxn];

const double step=0.2113248559;

void ready(){
	double opt=1e200,pos;
	
	for (double x=0.;x<0.5;x+=1e-9) {
		double v=2.*x+4.*sqrt(0.5-x+x*x);
		
		if (v<opt) opt=v,pos=x;
	}
	
	printf("%.10f\n",pos);
}

inline double dist(const int& a,const double& xx,const double& yy) {
	return sqrt((x[a]-xx)*(x[a]-xx)+(y[a]-yy)*(y[a]-yy));
}

inline double calc(const int& k,const double& a,const double& b,const double& c,const double& d) {

//	cout << x[k] << ' ' << y[k] << ' ' << a << ' ' << b << ' ' << c << ' ' << d << endl;	
	
	double len = sqrt((a - c) * (a - c) + (b - d) * (b - d));
	double lam=((x[k]-a)*(c-a)+(y[k]-b)*(d-b));
	
	lam /= len;
	
//	cout << lam << ' ' << len << endl;
	
	if (lam<1e-8||lam>len-1e-8) return min(dist(k,a,b),dist(k,c,d));
	
	return sqrt((x[k]-a)*(x[k]-a)+(y[k]-b)*(y[k]-b)-lam*lam);
}

void work() {
	double tot=0.;
	
	for (int i=0;i<n;i++) {
		v[i]=min(calc(i,0.,0.,0.5-step,0.5),calc(i,0.,1.,0.5-step,0.5));
		v[i]=min(v[i],min(calc(i,1.,0.,0.5+step,0.5),calc(i,1.,1.,0.5+step,0.5)));
		v[i]=min(v[i],calc(i,0.5-step,0.5,0.5+step,0.5));
		tot += v[i];
	}
	
	for (int i=0;i<n;i++) 
		for (int j=0;j<n;j++) if (i!=j) {
//		cout << v[i] << ' ' << v[j] << endl;
		double opt=tot-v[i]-v[j]+dist(i,0.5-step,0.5)+dist(j,0.5+step,0.5);	
				
		if (ans<0.||ans>opt) ans=opt;
	}
}

int main(){
	//ready();
	
	//printf("%.10f\n",2.*step+4.*sqrt(0.5-step+step*step));
	
	while (scanf("%d",&n)==1&&n) {
		ans=-1.;
		
		for (int i=0;i<n;i++) scanf("%lf%lf",&x[i],&y[i]);
		
		if (n==1) {
			printf("%.3f\n",dist(0,0.5,0.5)); continue;
		}
		
		work();
		
		for (int i=0;i<n;i++) swap(x[i],y[i]);
		
		work();
		
		printf("%.3f\n",ans);
	}

	return 0;
}
