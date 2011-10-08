#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define maxn (2005)
#define PB push_back
 
double x[maxn], y[maxn];
int n, R;
double r;
vector<double> a, b;

const double pi = acos(-1.);

void intersect(int i, int j) {
	double alpha = atan2(y[j] - y[i], x[j] - x[i]);
	
	double dist = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
	if (dist >= 2. * r) return ;
	
	double theta = acos(dist / (2. * r));
	double x1 = alpha - theta, x2 = alpha + theta;
	
	if (x1 < 0.) x1 += pi * 2., x2 += pi * 2.;
	if (x2 > pi * 2.) a.PB(0.), b.PB(x2 - pi * 2.), a.PB(x1), b.PB(pi * 2.);
	else a.PB(x1), b.PB(x2);
}

void work() {
	r = (double) R + 0.001;
	for (int i = 1; i <= n; ++i) scanf("%lf%lf", &x[i], &y[i]);
	
	int ans = 1;
	for (int i = 1; i <= n; ++i) {
		a.clear(), b.clear();
		
		for (int j = 1; j <= n; ++j) if (i != j) intersect(i, j);
		
		sort(a.begin(), a.end());
		sort(b.begin(), b.end());
		
		vector<double>::iterator A = a.begin();
		vector<double>::iterator B = b.begin();
		int cnt = 1;
		while (A != a.end()) {
			double now = *A;
			
			while (A != a.end() && *A <= now) cnt++, A++;
			while (B != b.end() && *B <= now) cnt--, B++;
			
			ans = max(ans, cnt);
		}
		
		ans = max(ans, cnt);
	}
	
	printf("It is possible to cover %d points.\n", ans);
}

int main() {
	while (scanf("%d%d", &n, &R) == 2 && (n || R)) work();

	return 0;
}

/*
Sample Input 

8 2 
1 2 
5 3 
5 4 
1 4 
8 2 
4 5 
7 5 
3 3

2 100 
0 100 
0 -100 

0 0

Sample Output 

It is possible to cover 4 points. 
It is possible to cover 2 points.
*/
