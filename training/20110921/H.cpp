#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
double f[17][17];
	int m;
void print() {
	for (int i = 1; i <= m; ++ i) {
		for (int j = 1; j <= m; ++ j)
			printf("%.3f ", f[i][j]);
		puts("");;
	}
		puts("");;
}

int main(){
	scanf("%d",&m);
	for(int i=0;i<12;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		f[x][x]++;
		f[y][y]++;
		f[x][y]--;
		f[y][x]--;
	}
	double ans=1;
/*	for(int i=1;i<=m;++i){
		double tmp=f[i][i];
		printf("%.2f\n",tmp);
		ans*=tmp;
		for(int j=i;j<=m;++j)
			f[i][j]/=tmp;
		for(int j=i+1;j<=m;++j){
			double v=f[j][i];
			for(int k=i;k<=m;++k)
				f[j][k]-=f[i][k]*v;
		}
	}*/
	print();
	m --;
	print();
	for (int i = 1; i <= m; ++ i) {
		for (int j = i + 1; j <= m; ++ j)
			for (int k = m; k >= i; -- k)
				f[j][k] = f[j][k] - f[i][k] * f[j][i] / f[i][i];
		print();
	}
	for (int i = 1; i <= m; ++ i)
		ans *= f[i][i];
	printf("%.10f\n",ans);
	return 0;
}
