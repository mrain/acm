#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const double delta=-acos(-1.)/4;

double ans,X,Y;
int t;

inline double dist(const double& a,const double& b,const double& c,const double& d) {
	return sqrt((a-c)*(a-c)+(b-d)*(b-d));
}

void dfs(int step,double x,double y,double alpha) {
	double d=dist(x,y,X,Y);
	
	//if (dist<3.) printf("%f %f : %f\n"x,y,d);
	
	ans=min(ans,d);

	if (d>((double)(t-step))*10.+ans) return ;

	if (step>=t) return ;
	
	dfs(step+1,x,y,alpha+delta);
	
	x+=10.*cos(alpha),y+=10.*sin(alpha);
	dfs(step+1,x,y,alpha);
}

int main() {
	int T; scanf("%d",&T);
	
	while (T--) {
		scanf("%d%lf%lf",&t,&X,&Y); ans=dist(0.,0.,X,Y);
		
		dfs(0,0.,0.,0.);
		
		printf("%.6f\n",ans);
	}

	return 0;
} 
