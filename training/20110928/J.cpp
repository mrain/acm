#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
int n,m,pre[101];
vector<double> a[101],b[101];
double d[101], ans;
bool vis[101];

ostream &operator <<(ostream &os, const vector<double> &t) {
	os << '(';
	for (int i = 0; i < (int)t.size(); ++ i)
		os << (i == 0 ? "" : ",") << t[i];
	os << ')';
}

double calc(vector<double> &r){
	double ret=0;
	for(int i=0;i<r.size();++i)
		ret+=r[i]*r[i];
	return ret;
}
vector<double> calc(vector<double> &x,vector<double> &y){
	double A, B, C; A = B = C = 0.;
	
	for (int i = 0; i < m; ++i) A += x[i] * x[i], B += -2. * x[i] * y[i], C += y[i] * y[i];
	
	double r;
	if (A == 0.) {
		if (B == 0.) r = 0.;
		else r = C / B; 
	}
	else r = - B / A * 0.5;
	
	vector<double> ret; ret.clear();
	for (int i = 0; i < m; ++i) ret.push_back(y[i] - x[i] * r);
	
	return ret;
}

void wu1() {
	/*static int p[101];
	for (int i = 1; i <= n; ++ i) p[i] = i;
	random_shuffle(p + 1, p + n + 1);*/
	random_shuffle(a + 1, a + n + 1);
	
	for(int i=1;i<=n;++i){
		int tot=1;
		b[tot].clear();
		b[tot]=a[i];
		for(int j=1;j<=n;++j)vis[j]=0;
		d[i]=0;vis[i]=1;
		for(int j=1;j<=n;++j){
			vector<double> tmp=calc(b[tot],a[j]);
			d[j]=calc(tmp);
			pre[j]=tot;
		}
		double v=calc(b[tot]);
		while(tot<n){
			double minv=1e100;
			int s1;
			for(int j=1;j<=n;++j)
				if(!vis[j])
					if(d[j]<minv)
						minv=d[j],s1=j;
			vis[s1]=1;
			b[++tot]=calc(b[pre[s1]],a[s1]);
			v+=calc(b[tot]);
			for(int j=1;j<=n;++j)
				if(!vis[j]){
					vector<double> tmp=calc(b[tot],a[j]);
					double ttmp=calc(tmp);
					if(ttmp<d[j]){
						d[j]=ttmp;
						pre[j]=tot;
					}
				}
		}
		if(v<ans)ans=v;
	}
}

void wu2() {
	//memset(vis, 0, sizeof(vis));
	random_shuffle(a + 1, a + n + 1);
	double now = 0;
	for (int i = 1; i <= n; ++ i) {
//		vector <double> pu = a[i];
		b[i] = a[i];
		double cur = calc(a[i]);
		for (int j = 1; j < i; ++ j) {
			//cout << b[j] << " " << a[i] << endl;
			vector<double> tmp = calc(b[j], a[i]);
			double ttmp = calc(tmp);
			if (ttmp < cur) cur = ttmp, b[i] = tmp;
		}
		now += cur;
	}
	ans = min(ans, now);
}



int main(){
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			double x;
			scanf("%lf",&x);
			a[i].push_back(x);
		}
	ans=1e100;
	wu1(); wu2();
	//for (int tt = 0; tt < 10000; ++ tt) wu2();
	printf("%.10f\n",ans);
	return 0;
}
