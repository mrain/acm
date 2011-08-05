#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

double feq[40], f[40][40], a[40][40], ans;
int tests, n, l[40][40];
string output;

void gen(int i, int j) {
	if (i == 0) return;
	int p = l[i][j];
	gen(p - 1, j - 1);
	output += ' ';
	for (int k = p; k <= i; ++ k) {
		//cout << k << ' ' << k - p + 1 << endl;
		ans += feq[k] * (double)(k - p + 1);
		output += ((char)(k + 'A' - 1));
	}
}

int main() {
	scanf("%d", &tests);
	int ca = 0;
	while (tests --) {
		scanf("%d", &n);
		for (int i = 1; i <= 26; ++ i) scanf("%lf", &feq[i]);
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= 26; ++ i)
			for (int j = 1; j <= i; ++ j) {
				a[j][i] = 0;
				for (int k = j; k <= i; ++ k)
					a[j][i] += (double)(k - j + 1) * feq[k];
			}
		for (int i = 0; i <= 26; ++ i)
			for (int j = 0; j <= n; ++ j)
				f[i][j] = 1e100;
		f[0][0] = 0;
		for (int i = 1; i <= 26; ++ i)
			for (int j = 1; j <= n; ++ j)
				for (int p = 1; p <= i; ++ p) {
					if (i - p + 1 > 8) continue;
					double tmp = a[p][i] + f[p - 1][j - 1];
					if (tmp < f[i][j]) {
						f[i][j] = tmp;
						l[i][j] = p;
					}
				}
		output = ""; ans = 0;
		gen(26, n);
		printf("%d %.3f", ++ ca, ans / 100.);
		puts(output.c_str());
	}
	return 0;
}
