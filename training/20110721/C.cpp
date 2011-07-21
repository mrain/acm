#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

#define maxn (10001)
const double pi = acos(-1.);
struct mat1{
	double g[3];
	
	void clear() {
		memset(g,0,sizeof(g));
	}
	
	mat1(){
	//	memset(g,0,sizeof(g));
	}
	
	mat1(const double &a,const double &b) {
		g[0]=a,g[1]=b; g[2]=1.;
	}
	
};

struct mat2{
	double g[3][3];
	
	void clear() {
		memset(g,0,sizeof(g));
	}
	
	mat2(){
		clear();
		g[0][0]=g[1][1]=g[2][2]=1.;
	}
	
	mat2(const double &a){
		//clear();
		g[0][0]=cos(a),g[0][1]=sin(a),g[1][0]=-sin(a),g[1][1]=cos(a);
		g[2][2]=1.;
		g[0][2]=g[1][2]=g[2][0]=g[2][1]=0.;
	}
	
	mat2(const double &a,const double &b){
		memset(g,0,sizeof(g));
		g[0][0]=g[1][1]=g[2][2]=1.;
		g[0][2]=a,g[1][2]=b;
	}
};

mat1 m21(const mat2& a,const mat1& b) {
	mat1 ret;
	
	ret.g[0]=a.g[0][0]*b.g[0]+a.g[0][1]*b.g[1]+a.g[0][2]*b.g[2];
	ret.g[1]=a.g[1][0]*b.g[0]+a.g[1][1]*b.g[1]+a.g[1][2]*b.g[2];/*
	for (int k=0;k<2;k++)
		for (int i=0;i<3;i++)
			ret.g[k]+=a.g[k][i]*b.g[i];*/
	ret.g[2]=1.;
			
	return ret;
}

mat2 m22(const mat2& a,const mat2& b) {
	mat2 ret;
	
ret.g[0][0]=a.g[0][0]*b.g[0][0]+a.g[0][1]*b.g[1][0]+a.g[0][2]*b.g[2][0];
ret.g[0][1]=a.g[0][0]*b.g[0][1]+a.g[0][1]*b.g[1][1]+a.g[0][2]*b.g[2][1];
ret.g[0][2]=a.g[0][0]*b.g[0][2]+a.g[0][1]*b.g[1][2]+a.g[0][2]*b.g[2][2];
ret.g[1][0]=a.g[1][0]*b.g[0][0]+a.g[1][1]*b.g[1][0]+a.g[1][2]*b.g[2][0];
ret.g[1][1]=a.g[1][0]*b.g[0][1]+a.g[1][1]*b.g[1][1]+a.g[1][2]*b.g[2][1];
ret.g[1][2]=a.g[1][0]*b.g[0][2]+a.g[1][1]*b.g[1][2]+a.g[1][2]*b.g[2][2];
		ret.g[2][2]=1.;
				
	return ret;
}

const double torad=acos(-1.)/180.;
mat2 f[maxn*8+1];
bool flag[maxn*8+1];
mat1 s[maxn+1];
int m,n,cases;
//mat2 P;

void build(int x,int st,int ed) {
	flag[x]=false;
	if (st==ed) {
//		f[x]=mat2();
		return ; 
	}
	
	int mid=(st+ed)>>1;
	
	build(x+x,st,mid),build(x+x+1,mid+1,ed);
}

void fresh(int p) {
	int x=1,st=1,ed=n;
//	mat2 res;
	int mid;
	while (true) {
		if (st==ed) {
			if (flag[x]) s[p]=m21(f[x],s[p]);
			if (flag[x]) f[x]=mat2(), flag[x]=false;
			break;
		}
		
		if (flag[x]) {
			if (flag[x+x]) f[x+x]=m22(f[x],f[x+x]);
			else f[x+x]=f[x];
			if (flag[x+x+1]) f[x+x+1]=m22(f[x],f[x+x+1]);
			else f[x+x+1]=f[x];
			f[x]=mat2();
			flag[x+x]=flag[x+x+1]=true; flag[x]=false;
		}
		
		mid=(st+ed)>>1;
		if (p<=mid) x=x+x,ed=mid;
		else x=x+x+1,st=mid+1;
	}
}

void cover(int x,int st,int ed,int p,int q,const mat2& m) {
	if (st>=p&&ed<=q) {
		//f[x]=m22(m,f[x]);
		if (flag[x]) f[x]=m22(m,f[x]);
		else f[x]=m;
		flag[x]=true;
		return ;
	}
	
	if (flag[x]) {
		if (flag[x+x]) f[x+x]=m22(f[x],f[x+x]);
		else f[x+x]=f[x];
		if (flag[x+x+1]) f[x+x+1]=m22(f[x],f[x+x+1]);
		else f[x+x+1]=f[x];
		f[x]=mat2();
		flag[x+x]=flag[x+x+1]=true; flag[x]=false;
	}
	
	register int mid=(st+ed)>>1;
	
	if (p<=mid) cover(x+x,st,mid,p,q,m);
	if (q>mid) cover(x+x+1,mid+1,ed,p,q,m);
}

#define len(x,y) (sqrt((x)*(x)+(y)*(y)))
#define cross(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))

inline double calc(double x1, double y1, double x2, double y2, double x3, double y3) {
	double a = len(x1-x2, y1-y2), b=len(x3-x2,y3-y2), c=len(x3-x1,y3-y1);
//	cout << a << ' ' << b << ' ' << c << endl;
	double cc = (a*a+b*b-c*c)/(2*a*b);
	double firstr;
	if (cc > 1. - 1e-10) firstr = 0;
	else if (cc < -1. + 1e-10) firstr = pi;
	else firstr = acos(cc);
	if (cross(x2-x1,y2-y1,x3-x2,y3-y2) >= -1e-8) return 2*pi-firstr;
	else return firstr;
}
/*
void print(const mat2 &m) {
		for (int i = 0; i < 3; ++ i) {
			for (int j = 0; j < 3; ++ j)
				cout<<m.g[i][j] << ' ';
			cout << endl;
		}
}*/

void work(){
	if (cases) puts(""); cases++;
//	memset(flag,0,sizeof(flag));

	for (int i=1;i<=n;i++) scanf("%lf",&(s[i].g[1]));
	for (int i=1;i<=n;i++) s[i].g[1]+=s[i-1].g[1],s[i].g[0]=0.,s[i].g[2]=1.;
//	cout.setf(ios::fixed);
//	cout.precision(10);
	build(1,1,n);
	
	
	for (int i=0;i<m;i++) {
//		cout << "================" << i << "=================" << endl;
		int pos; double rad;
		scanf("%d%lf",&pos,&rad);
		
//		cout << rad << endl;
		rad=rad*torad;
		
		if (pos>1) fresh(pos-1);
		fresh(pos);
		fresh(pos + 1);
		
		double tmpr = calc(s[pos - 1].g[0], s[pos - 1].g[1], s[pos].g[0], s[pos].g[1], s[pos + 1].g[0], s[pos + 1].g[1]);
/*
		cout << s[pos - 1].g[0] << ' ' << s[pos - 1].g[1] << endl;
		cout << s[pos - 0].g[0] << ' ' << s[pos - 0].g[1] << endl;
		cout << s[pos + 1].g[0] << ' ' << s[pos + 1].g[1] << endl;
		cout << tmpr << endl;
		cout << rad << endl;
*/		
		//cout << tmpr << endl;
		rad = tmpr-rad;
//		cout << X[pos] << ' ' << Y[pos] << endl;
//		cout << rad << endl;
		
		mat2 A=mat2(s[pos].g[0],s[pos].g[1]),B=mat2(rad),C=m22(A,B),D=mat2(-s[pos].g[0],-s[pos].g[1]);
/*		
		cout << "A" << endl;
		print(A);
		cout << "B" << endl;
		print(B);
		cout << "D" << endl;
		print(D);
*/
		mat2 m=m22(C,D);
		
		
		cover(1,1,n,pos+1,n,m);
		fresh(n);
		
		if (fabs(s[n].g[0]) < 1e-8) s[n].g[0] = 0;
		if (fabs(s[n].g[1]) < 1e-8) s[n].g[1] = 0;
		printf("%.2f %.2f\n",s[n].g[0],s[n].g[1]);
	}
}

int main(){

	while (scanf("%d%d",&n,&m)==2) work();

	return 0;
}
