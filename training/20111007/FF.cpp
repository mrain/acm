#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

#define maxn (3205)

double F[2][maxn];
double d[maxn], ans[maxn];

int main() {
/*
	int n = 20;

	for (int k = 1; k <= n; ++k) {
		int tot = 0;
	
		for (int i = 0; i < 1 << (k - 1); ++i) {
			int opt = 0, opt2 = 0;
		
			for (int a = 0; a < k; ++a) {
				int cnt = 0;
				for (int b = a; b < k; ++b) {
					if (i & (1 << b)) cnt++;
					else cnt--;
					
					opt = max(opt, abs(cnt));
//					opt2 = min(opt2, cnt2);
				}
			}
			//cout << i << ' ' << opt << endl;
			tot += opt;
		}
		
		printf("%d =  %d / %d, %f\n", k, tot, 1 << (k - 1), (double) tot / (double) (1 << (k - 1)));
	}
*/
	int now = 0; F[now][0] = 1.;
	
	for (int i = 1; i <= 3100; i ++) {
		int to = now ^ 1;
		F[to][0] = F[now][0] * 0.5;
		//cout << F[to][0] << ' ';
		for (int j = 1; j <= i; ++j) {
			F[to][j] = (F[now][j - 1] + F[now][j]) * 0.5;
			//cout << F[to][j] << ' ';
		}
		//cout << endl;
		
		now = to;
		
		if (i % 2 == 1) {
			int x = i / 2; d[x] = F[now][x];
			//cout << i << ' ' << x << ' ' << F[now][x] << endl;
		}
	}
	//return 0;
	
	ans[1] = 1.;
	for (int i = 2; i <= 3000; i += 2) {
		int x = i / 2 - 1;
		ans[i] = ans[i - 1] + d[x]; ans[i + 1] = ans[i] + d[x];	
	}

	//for (int i = 1; i <= 20; ++i) printf("%.6f\n", ans[i]);
	scanf("%d", &now);
	int ca = 0;
	while (now --) {
		int n;
		scanf("%d", &n);
		printf("Case %d: %.6f\n", ++ ca, ans[n]);
	}

	return 0;
} 
